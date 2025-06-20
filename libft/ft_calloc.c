/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktroude <ktroude@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:35:53 by ktroude           #+#    #+#             */
/*   Updated: 2021/10/29 19:11:16 by ktroude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char		*str;
	size_t		i;

	i = 0;
	str = malloc (count * size);
	if (!str)
		return (NULL);
	while (i != count * size)
		str[i++] = 0;
	return ((void *) str);
}
