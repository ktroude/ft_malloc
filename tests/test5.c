#include <unistd.h>
#include <string.h>
#include "../include/malloc.h"

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
	char *addr;

	print("\nBefore bad free:\n");
	show_alloc_mem();

	addr = malloc(16);
	free(NULL);
	free((void *)addr + 5);

	if (realloc((void *)addr + 5, 10) == NULL)
		print("Bonjours\n");

	print("\nAfter bad realloc:\n");
	show_alloc_mem();

	return (0);
}
