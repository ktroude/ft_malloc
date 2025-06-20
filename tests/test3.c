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

int main()
{
	char *addr1;
	char *addr3;

	print("\nBefore first malloc:\n");
	show_alloc_mem();

	addr1 = (char*)malloc(16 * M);
	strcpy(addr1, "Bonjour\n");
	print(addr1);

	print("\nBefore realloc:\n");
	show_alloc_mem();

	addr3 = (char*)realloc(addr1, 128 * M);
	addr3[127 * M] = 42;
	print(addr3);

	print("\nAfter realloc:\n");
	show_alloc_mem();

	return (0);
}
