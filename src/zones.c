#include "malloc.h"

/**
 * @brief Searches for a free block in existing zones.
 *
 * This function traverses the linked list of zones and their blocks to find
 * a free block that can accommodate the requested size. If a suitable block
 * is found, it is marked as used and potentially split if it's larger than needed.
 * 
 * The function also supports lazy allocation by
 * creating new blocks on-demand within existing zones if space permits.
 *
 * @param zone Pointer to the first zone in the linked list.
 * @param size The size of memory requested (already aligned).
 *
 * @return Pointer to the usable memory (after the block header), or NULL if
 *         no suitable free block is found.
 */
static void *find_free_block(t_zone *zone, size_t size) {
    while (zone) {
        t_block *block = zone->blocks;
        t_block *last_block = NULL;
        
        while (block) {
            if (block->is_free && block->size >= size) {
                block->is_free = 0;
                
                if (block->size == size) {
                    return (void *)(block + 1);
                }
                
                if (block->size > size + sizeof(t_block) + ALIGNMENT) {
                    t_block *new_block = (t_block *)((char *)block + sizeof(t_block) + size);
                    new_block->size = block->size - size - sizeof(t_block);
                    new_block->is_free = 1;
                    new_block->next = block->next;
                    
                    block->size = size;
                    block->next = new_block;
                }
                
                return (void *)(block + 1);
            }
            last_block = block;
            block = block->next;
        }
        
        if (last_block != NULL) {
            char *next_pos = (char *)last_block + sizeof(t_block) + last_block->size;
            char *zone_end = (char *)zone + zone->size;
            
            if (next_pos + sizeof(t_block) + size <= zone_end) {
                t_block *new_block = (t_block *)next_pos;
                new_block->size = size;
                new_block->is_free = 0;
                new_block->next = NULL;
                
                last_block->next = new_block;
                
                return (void *)(new_block + 1);
            }
        }
        
        zone = zone->next;
    }
    return NULL;
}

/**
 * @brief Creates a new zone and allocates the first block within it.
 *
 * This function uses mmap to create a new memory zone of the specified size.
 * For LARGE allocations (> SMALL_THRESHOLD), the zone contains a single block.
 * For TINY/SMALL allocations, the zone is created with lazy allocation strategy:
 * only the first block is initialized, and subsequent blocks are created on-demand.
 *
 * The function first attempts to find space in existing zones before creating a new one.
 *
 * @param zone_list Pointer to the head of the zone list (passed by reference).
 * @param size The size of the block to allocate (already aligned).
 * @param zone_size The total size of the zone to create.
 *
 * @return Pointer to the usable memory of the allocated block, or NULL on failure.
 */
static void *create_zone_with_block(t_zone **zone_list, size_t size, size_t zone_size) {
    if (*zone_list != NULL) {
        void *ret = find_free_block(*zone_list, size);
        if (ret != NULL) {
            return ret;
        }
    }

    t_zone *zone = mmap(NULL, zone_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

    if (zone == MAP_FAILED) {
        return NULL;
    }

    zone->size = zone_size;
    zone->next = NULL;

    if (size > SMALL_THRESHOLD) {
        t_block *block = (t_block *)(zone + 1);
        block->size = size;
        block->is_free = 0;
        block->next = NULL;
        
        zone->blocks = block;
        zone->next = *zone_list;
        *zone_list = zone;
        
        return (void *)(block + 1);
    }

    t_block *first_block = (t_block *)(zone + 1);
    first_block->size = size;
    first_block->is_free = 0;
    first_block->next = NULL;
    
    zone->blocks = first_block;
    
    zone->next = *zone_list;
    *zone_list = zone;
    
    return (void *)(first_block + 1);
}

/**
 * @brief Allocates a memory block within a zone.
 *
 * This is the main allocation function that first searches for a suitable
 * free block in existing zones. If no free block is found, it creates a
 * new zone with the requested block.
 *
 * @param zone_list Pointer to the head of the zone list (TINY, SMALL, or LARGE).
 * @param size The size of memory to allocate (already aligned).
 * @param zone_size The size of zones to create for this allocation type.
 *
 * @return Pointer to the allocated memory, or NULL if allocation fails.
 */
void *alloc_in_zone(t_zone **zone_list, size_t size, size_t zone_size) {
    void *ret = find_free_block(*zone_list, size);

    if (ret == NULL) {
        ret = create_zone_with_block(zone_list, size, zone_size);
    }

    return ret;
}

/**
 * @brief Searches for a specific block in a zone list.
 *
 * This function is used by free() to verify that a given block pointer
 * belongs to a specific zone list (TINY, SMALL, or LARGE). It traverses
 * all zones and their blocks to find a match.
 *
 * @param zone The head of the zone list to search.
 * @param block The block pointer to search for.
 *
 * @return The block pointer if found, NULL otherwise.
 */

t_block *find_block_in_zone(t_zone *zone, t_block *block) {
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
 * @brief Finds the zone containing a specific block in the LARGE zone list.
 *
 * This function is specifically designed for LARGE allocations where each
 * zone contains only one block. It's used by free() to locate the zone
 * that needs to be unmapped when freeing a LARGE allocation.
 *
 * @param zone The head of the LARGE zone list.
 * @param block The block to search for.
 *
 * @return Pointer to the zone containing the block, or NULL if not found.
 */
t_zone *find_zone_in_large_list(t_zone *zone, t_block *block) {
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
