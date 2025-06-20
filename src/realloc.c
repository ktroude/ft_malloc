#include "malloc.h"

/**
 * @brief Retrieves the metadata block associated with a pointer.
 *
 * This function assumes that the pointer comes from malloc (i.e. points
 * to the user data, right after the t_block header).
 * It searches the TINY, SMALL and LARGE zone lists for the block.
 *
 * @param ptr Pointer returned by malloc().
 * @return Pointer to the corresponding t_block, or NULL if not found.
 */
static t_block *get_block_from_ptr(void *ptr) {
    if (ptr == NULL) {
        return NULL;
    }

    t_block *block = ((t_block *)ptr) - 1;

    if (find_block_in_zone(g_malloc.tiny, block)) {
        return block;
    }
    if (find_block_in_zone(g_malloc.small, block)) {
        return block;
    }
    if (find_zone_in_large_list(g_malloc.large, block)) {
        return block;
    }

    return NULL;
}

/**
 * @brief Attempts to reallocate memory to a new size.
 *
 * If `ptr` is NULL, behaves like malloc(size).
 * If `size` is 0, behaves like free(ptr).
 * If the block has enough space, returns the same pointer.
 * Otherwise, allocates a new block, copies the data, and frees the old one.
 *
 * @param ptr Pointer to the memory block to reallocate.
 * @param size New size in bytes.
 * @return Pointer to the reallocated memory, or NULL on error.
 */
void *realloc(void *ptr, size_t size) {

    if (ptr == NULL) {
        return malloc(size);
    }

    if (size == 0) {
        free(ptr);
        return NULL;
    }

    size_t aligned = align_size(size);
    t_block *block = get_block_from_ptr(ptr);

    if (block->size >= aligned) {
        return ptr;
    }
    
    void *new_ptr = malloc(size);
    if (new_ptr == NULL) {
        return NULL;
    }

    memcpy(new_ptr, ptr, block->size);
    free(ptr);

    return new_ptr;
}
