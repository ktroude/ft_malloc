#include "malloc.h"

/**
 * @brief Global memory allocator state.
 *
 * Contains the heads of the zone lists (TINY, SMALL, LARGE) and a mutex
 * to protect all memory operations in a multithreaded context.
 */
t_malloc g_malloc = {
    .tiny = NULL,
    .small = NULL,
    .large = NULL,
    .lock = PTHREAD_MUTEX_INITIALIZER
};

/**
 * @brief Determines the appropriate zone type for the requested allocation size.
 *
 * Based on the size, this function decides whether the allocation should go in
 * the TINY, SMALL, or LARGE zone. It also sets the corresponding zone size
 * that should be used for mmap if a new zone is required.
 *
 * @param size The requested allocation size (aligned or raw, doesn't matter).
 * @param zone_size Output pointer where the zone size will be stored.
 *
 * @return A pointer to the appropriate zone list (tiny, small, or large).
 */
static t_zone **get_target_zone(size_t size, size_t *zone_size) {
    if (size <= TINY_THRESHOLD)
    {
        *zone_size = TINY_ZONE_SIZE;
        return &g_malloc.tiny;
    }

    if (size <= SMALL_THRESHOLD)
    {
        *zone_size = SMALL_ZONE_SIZE;
        return &g_malloc.small; 
    }

    *zone_size = size + sizeof(t_block);
    return &g_malloc.large;
}

/**
 * @brief Custom implementation of malloc().
 *
 * This function replaces the standard malloc. It determines the appropriate zone
 * for the requested size, attempts to allocate a block in an existing zone,
 * or creates a new one if necessary.
 *
 * Thread safety is ensured using a global mutex.
 *
 * @param size The size of memory to allocate in bytes.
 *
 * @return A pointer to the usable memory block, or NULL if allocation fails.
 */
void *malloc(size_t size) {

    if (size == 0) {
        return NULL;
    }
    
    pthread_mutex_lock(&g_malloc.lock);

    size_t aligned = align_size(size);
    size_t zone_size;

    t_zone **zone_list = get_target_zone(size, &zone_size);

    void *ptr = alloc_in_zone(zone_list, aligned, zone_size);

    pthread_mutex_unlock(&g_malloc.lock);

    return ptr;
}
