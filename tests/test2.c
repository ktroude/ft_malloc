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

	print("\n\nBefore first malloc:\n");
	show_alloc_mem();

	i = 0;
	while (i < 1024)
	{
		addr = (char *)malloc(1024);
		if (i == 0)
		{
			print("\n\nFIRST ALLOCATION :\n");
			print("After malloc and before free:\n");
			show_alloc_mem();
        }
        if (i == 1023)
		{
			print("\n\nLAST ALLOCATION :\n");
			print("After malloc and before free:\n");
			show_alloc_mem();
		}
		addr[0] = 42;
		free(addr);
		if (i == 0)
		{
			print("\n\nFIRST ALLOCATION :\n");
			print("After free:\n");
			show_alloc_mem();
		}
        if (i == 1023)
		{
			print("\n\nLAST ALLOCATION :\n");
			print("After free:\n");
			show_alloc_mem();
		}
		i++;
	}

	print("\n\nFinal allocation memory:\n");
	show_alloc_mem();
	return (0);
}
