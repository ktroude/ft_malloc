#include "../include/malloc.h"
#include <unistd.h>

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

int	main(void)
{
	int		i;
	char	*addr;

	print("\nBefore loop of allocations:\n");
	show_alloc_mem();

	i = 0;
	while (i < 1024)
	{
		addr = (char*)malloc(1024);
		addr[0] = 42;
		i++;
	}

	print("\nAfter loop of allocations:\n");
	show_alloc_mem();
	return (0);
}
