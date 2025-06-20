#include "../include/malloc.h"
#include <unistd.h>

void print(const char *s)
{
	size_t len = 0;
	while (s[len])
		len++;
	write(1, s, len);
}

int	main(void)
{
	print("Before all malloc:\n");
	show_alloc_mem();

	malloc(1);
	malloc(1024);
	malloc(1024 * 32);
	malloc(1024 * 1024);
	malloc(1024 * 1024 * 16);
	malloc(1024 * 1024 * 128);

	print("\nAfter all malloc:\n");
	show_alloc_mem();

	return (0);
}
