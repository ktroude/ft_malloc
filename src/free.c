#include "malloc.h"

/**
 * @brief Searches for a given block in a list of zones (TINY or SMALL).
 *
 * Iterates over all blocks in all zones of the given list and returns the matching
 * block pointer if found.
 *
 * @param zone Pointer to the head of a zone list.
 * @param block Pointer to the block being searched.
 * @return Pointer to the matching block if found, NULL otherwise.
 */
static t_block *find_block_in_zone(t_zone *zone, t_block *block) {
    if (zone == NULL) {
        return NULL;
    }

    t_zone *curr_zone = zone;

    while (curr_zone) {
        t_block *curr_block = curr_zone->blocks;
        while (curr_block) {
            if (curr_block == block) {
                return block;
            }
            curr_block = curr_block->next;
        }
        curr_zone = curr_zone->next;
    }

    return NULL;
}

/**
 * @brief Finds the zone in the LARGE list that contains a given block.
 *
 * Because each LARGE zone contains only one block, the match is done directly
 * between the zone's `blocks` field and the given block pointer.
 *
 * @param zone Head of the LARGE zones list.
 * @param block Pointer to the block to find.
 * @return Pointer to the zone containing the block, or NULL if not found.
 */
static t_zone *find_zone_in_large_list(t_zone *zone, t_block *block) {
    if (zone == NULL) {
        return NULL;
    }

    t_zone *curr_zone = zone;

    while (curr_zone) {
        if (curr_zone->blocks == block) {
            return curr_zone;
        }
        curr_zone = curr_zone->next;
    }

    return NULL;
}

/**
 * @brief Removes a zone from a linked list of zones.
 *
 * This function updates the zone list to remove the specified zone.
 * It safely handles the case where the zone is at the head of the list.
 *
 * @param start Pointer to the head of the list (passed by reference).
 * @param to_delete Zone to remove from the list.
 */
static void reorganize_linked_list(t_zone **start, t_zone *to_delete) {
    if (*start == to_delete) {
        *start = to_delete->next;
        return;
    }

    t_zone *curr = *start;

    while(curr) {
        if (curr->next && curr->next == to_delete) {
            curr->next = to_delete->next;
            break ;
        }
        curr = curr->next;
    }
}

/**
 * @brief Frees a previously allocated memory block.
 *
 * This function marks a block as free if it belongs to a TINY or SMALL zone.
 * If the block belongs to a LARGE zone (dedicated mmap), the entire zone is unmapped
 * and removed from the linked list of large zones.
 *
 * @param ptr Pointer to the memory block to free.
 * If NULL, the function does nothing.
 */
void free(void *ptr) {

    if (ptr == NULL) {
        return ;
    }

    t_block *block = ((t_block *)ptr) - 1;

    t_zone *tiny = g_malloc.tiny;
    t_zone *small = g_malloc.small;
    t_zone *large = g_malloc.large;

    t_block *block_found;

    block_found = find_block_in_zone(tiny, block);
    if (block_found) {
        block_found->is_free = 1;
        return;
    }

    block_found = find_block_in_zone(small, block);
    if (block_found) {
        block_found->is_free = 1;
        return;
    }

    t_zone *zone_found = find_zone_in_large_list(large, block);
    if (zone_found) {
        reorganize_linked_list(&g_malloc.large, zone_found);
        munmap(zone_found, zone_found->size);
    }
}
