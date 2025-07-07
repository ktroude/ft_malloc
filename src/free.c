#include "malloc.h"

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
        return;
    }

    pthread_mutex_lock(&g_malloc.lock);

    t_block *block = ((t_block *)ptr) - 1;

    // Vérifier dans tiny
    if (find_block_in_zone(g_malloc.tiny, block)) {
        block->is_free = 1;
        pthread_mutex_unlock(&g_malloc.lock);
        return;
    }

    // Vérifier dans small
    if (find_block_in_zone(g_malloc.small, block)) {
        block->is_free = 1;
        pthread_mutex_unlock(&g_malloc.lock);
        return;
    }

    // Vérifier dans large
    t_zone *zone_found = find_zone_in_large_list(g_malloc.large, block);
    if (zone_found) {
        reorganize_linked_list(&g_malloc.large, zone_found);
        munmap(zone_found, zone_found->size);
    }

    pthread_mutex_unlock(&g_malloc.lock);
}