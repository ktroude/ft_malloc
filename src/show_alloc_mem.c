#include "malloc.h"

/**
 * @brief Prints the memory range and size of a single allocated block.
 *
 * Calculates the start and end user memory addresses of a block
 * (skipping the metadata) and prints them with the number of allocated bytes.
 *
 * @param block Pointer to the allocated block.
 * @param bytes Number of user-visible bytes allocated in the block.
 */
static void print_ligne(t_block *block, int bytes) {
    void *start = (void *)(block + 1);
    void *end = (void *)((char *)start + bytes);
    printf("%p - %p : %d bytes\n", start, end, bytes);
}

/**
 * @brief Iterates over all allocated blocks in a given zone list.
 *
 * This function traverses all memory blocks in all zones starting from `zone`,
 * and for each block that is marked as used (not free), it prints its memory
 * range and adds its size to the total.
 *
 * @param zone Pointer to the start of a zone list (TINY, SMALL, or LARGE).
 * @return The total size (in bytes) of all allocated blocks in the list.
 */
static int get_allocation_loop(zone_t *zone) {
    int ret = 0;

    while(zone) {
        t_block *block = zone->blocks;
        while(block) {
            if (!block->is_free) {
                print_ligne(block, block->size);
                ret += block->size;
            }
            block = block->next;
        }
        zone = zone->next;
    }

    return ret;
}

/**
 * @brief Displays the current state of all memory allocations.
 *
 * Iterates through the TINY, SMALL, and LARGE memory zones and prints each
 * allocated block’s address range and size. Frees are not shown. At the end,
 * the total amount of allocated memory is printed.
 * 
 *  * Format example:
 * ```
 * TINY : 0xA0000
 * 0xA0020 - 0xA004A : 42 bytes
 * SMALL : 0xAD000
 * 0xAD020 - 0xADEAD : 3725 bytes
 * LARGE : 0xB0000
 * 0xB0020 - 0xBBEEF : 48847 bytes
 * Total : 52698 bytes
 * ```
 */
void show_alloc_mem() {

    int total = 0;

    printf("TINY : %p\n", (void *)g_malloc.tiny);
    total += get_allocation_loop(g_malloc.tiny);

    printf("SMALL : %p\n", (void *)g_malloc.small);
    total += get_allocation_loop(g_malloc.small);

    printf("LARGE : %p\n", (void *)g_malloc.large);
    total += get_allocation_loop(g_malloc.large);

    printf("Total : %d bytes\n", total);
}
