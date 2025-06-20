/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktroude <ktroude@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:14:44 by ktroude           #+#    #+#             */
/*   Updated: 2021/11/02 13:51:44 by ktroude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size_nb(long int nb)
{
	int	size;

	size = 1;
	if (nb < 0)
	{
		size++;
		nb = nb * -1;
	}
	while (nb > 9)
	{
		nb = nb / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	int			size;
	char		*str;
	long int	nb;
	int			sign;

	sign = 1;
	nb = n;
	str = malloc (sizeof (char) * (size = ft_size_nb(n)) + 1);
	if (!str)
		return (NULL);
	if (nb < 0)
		sign *= -1;
	str[size] = 0;
	while (size--)
	{
		str[size] = sign * nb % 10 + '0';
		nb = nb / 10;
	}
	if (sign < 0)
		str[++size] = '-';
	return (str);
}
