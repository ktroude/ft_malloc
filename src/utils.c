#include "malloc.h"

size_t align_size(size_t size) {
    return (size + ALIGNMENT - 1) & ~(ALIGNMENT - 1);
}

size_t page_size(void) {
    static size_t size = 0;
    if (size == 0)
        size = (size_t)sysconf(_SC_PAGESIZE);
    return size;
}

void    free_block(void *ptr) {

}