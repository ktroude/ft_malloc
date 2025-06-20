#include <unistd.h>
#include <string.h>
#include "../include/malloc.h"

#define M (1024 * 1024)

size_t ft_strlen(const char *s)
{
	size_t i = 0;
	while (s[i])
		i++;
	return i;
}

void print(const char *s)
{
	write(1, s, ft_strlen(s));
}

int main(void)
{
	char *addr1;
	char *addr2;
	char *addr3;

	print("\nBefore allocations:\n");
	show_alloc_mem();

	addr1 = malloc(16 * M);
	strcpy(addr1, "Bonjours\n");
	print(addr1);

	addr2 = malloc(16 * M);

	print("\nBefore realloc:\n");
	show_alloc_mem();

	addr3 = realloc(addr1, 128 * M);
	addr3[127 * M] = 42;
	print(addr3);

	print("\nAfter realloc:\n");
	show_alloc_mem();

	return (0);
}
