#include "malloc.h"


t_malloc g_malloc = {
    .tiny = NULL,
    .small = NULL,
    .large = NULL,
    .lock = PTHREAD_MUTEX_INITIALIZER
};

static t_zone **get_target_zone(size_t size, size_t *zone_size) {
    if (size <= TINY_THRESHOLD) {
        *zone_size = TINY_ZONE_SIZE;
        return &g_malloc.tiny;
    }
    else if (size <= SMALL_THRESHOLD) {
        *zone_size = SMALL_THRESHOLD;
        return &g_malloc.small; 
    }
    else {
        *zone_size = size + sizeof(t_block);
        return &g_malloc.large;
    }
}

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