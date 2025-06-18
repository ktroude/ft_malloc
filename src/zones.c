#include "malloc.h"

/**
 * @brief Allocates a memory block from an existing zone or creates a new one if needed.
 *
 * This function attempts to find a free memory block of at least the requested size
 * in the given zone list. If none is found, it maps a new zone using mmap and
 * returns a pointer to a newly created block.
 *
 * @param zone_list Pointer to the linked list of zones (TINY, SMALL, or LARGE).
 * @param size The aligned size to allocate (not including metadata).
 * @param zone_size The total size of the memory zone to allocate with mmap if needed.
 *
 * @return Pointer to the allocated memory area usable by the user (i.e. after block metadata),
 *         or NULL on failure.
 */
void *alloc_in_zone(t_zone **zone_list, size_t size, size_t zone_size) {
    t_zone *zone = *zone_list;
    void *ret = find_free_block(zone, size);

    if (ret == NULL) {
        ret = create_zone_with_block(zone_list, size, zone_size);
    }

    return ret;
}

/**
 * @brief Searches for a free memory block in the provided zones.
 *
 * Iterates over all blocks in the zones, looking for a block that is free
 * and large enough to fulfill the requested size. If such a block is found,
 * it is marked as used and its memory address is returned.
 *
 * @param zone The head of the linked list of memory zones to search.
 * @param size The aligned size of memory to allocate.
 *
 * @return Pointer to the usable memory area if a suitable block is found, or NULL otherwise.
 */
void *find_free_block(t_zone *zone, size_t size) {
    while (zone) {
            t_block *block = zone->blocks;
        while (block) {
            if (block->is_free && block->size >= size) {
                block->is_free = 0;
                return (void *)(block +1);
            }
            block = block->next;
        }
        zone = zone->next;
    }
    return NULL;
}

/**
 * @brief Creates a new memory zone and initializes a block within it.
 *
 * Uses mmap to allocate a new memory zone of the specified size, then
 * initializes a single memory block inside that zone to fulfill the requested size.
 * The new zone is inserted at the head of the zone list.
 *
 * @param zone_list Pointer to the zone list to which the new zone will be added.
 * @param size The aligned size to allocate inside the new zone.
 * @param zone_size The total size to allocate for the new zone.
 *
 * @return Pointer to the newly allocated memory block usable by the user,
 *         or NULL if mmap fails.
 */
void *create_zone_with_block(t_zone **zone_list, size_t size, size_t zone_size) {
    t_zone *zone = mmap(NULL, zone_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

    if (zone == MAP_FAILED) {
        return NULL;
    }

    memset(zone, 0, zone_size);

    t_block *block = (t_block *)(zone + 1);
    block->size = size;
    block->is_free = 0;
    zone->blocks = block;

    zone->next = *zone_list;
    *zone_list = zone;

    return (void *)(block + 1);
}