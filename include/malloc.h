#ifndef MALLOC_H
#define MALLOC_H

#include <stddef.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/resource.h>
#include <pthread.h>
#include <string.h>

#define TINY_THRESHOLD 128
#define SMALL_THRESHOLD 2048

#define TINY_ZONE_SIZE  (page_size() * 8)   // page_size = 4096;    4096 * 8 = 32768;      32768/128 = 256
#define SMALL_ZONE_SIZE (page_size() * 52)  // page_size = 4096;    4096 * 52 = 212992;    212992/2048 = 104

#define ALIGNMENT 16

typedef struct s_block {
    size_t size;
    int is_free;
    struct s_block *next;
} t_block;

typedef struct s_zone {
    size_t size;
    struct s_zone *next;
    t_block *blocks;
} t_zone;

typedef struct s_malloc {
    t_zone *tiny;
    t_zone *small;
    t_zone *large;
    pthread_mutex_t lock;
} t_malloc;

extern t_malloc g_malloc;

void    *malloc(size_t size);
void    free(void *ptr);
void    *realloc(void *ptr, size_t size);
void    show_alloc_mem(void);

size_t  align_size(size_t size);
void    *alloc_in_zone(t_zone **zone_list, size_t size, size_t zone_size);
t_block *find_block_in_zone(t_zone *zone, t_block *block);
t_zone  *find_zone_in_large_list(t_zone *zone, t_block *block);
size_t  page_size(void);
int	    ft_printf(const char *str, ...);

#endif
