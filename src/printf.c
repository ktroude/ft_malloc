#include "malloc.h"

static int ft_putnbr(int n)
{
	int				j;
	char			c;

	j = 0;
	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	if (n < 0)
	{
		n = n * -1;
		j += ft_putchar('-');
	}
	if (n > 9)
	{
		j += ft_putnbr(n / 10);
		j += ft_putnbr(n % 10);
	}
	if (n < 10)
	{
		c = n + 48;
		j += ft_putchar(c);
	}
	return (j);
}

static int ft_putnbr_base_p(unsigned long int n)
{
	int		j;
	char	*str;

	str = "0123456789abcdef";
	j = 0;
	if (n >= 16)
	{
		j += ft_putnbr_base_p(n / 16);
		j += ft_putnbr_base_p(n % 16);
	}
	if (n < 16)
			j += write(1, &str[n], 1);
	return (j);
}

static int check_printf(int i, const char *str, va_list args)
{
	if (str[i] == 'p')
	{
		write (1, "0x", 2);
		return (2 + ft_putnbr_base_p(va_arg(args, unsigned long int)));
	}
	if (str[i] == 'd' || str[i] == 'i')
		return (ft_putnbr(va_arg(args, int)));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		j;
	int		i;
	va_list	args;

	j = 0;
	i = 0;
	va_start (args, str);
	while (str[i])
	{
		if (str[i] != '%')
		{
			write(1, &str[i], 1);
			j++;
		}	
		if (str[i] == '%')
		{
			i++;
			j += check_printf(i, str, args);
		}
		i++;
	}
	va_end(args);
	return (j);
}
