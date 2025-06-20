/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktroude <ktroude@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:31:01 by ktroude           #+#    #+#             */
/*   Updated: 2021/10/29 19:15:03 by ktroude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dst1;
	char	*src2;
	int		i;

	i = 0;
	dst1 = (char *)dst;
	src2 = (char *)src;
	if (!(dst || src))
		return (NULL);
	if ((size_t)dst - (size_t)src < len)
	{
		while (len--)
			dst1[len] = src2[len];
		return ((void *)dst1);
	}
	while (len--)
	{
		dst1[i] = src2[i];
		i++;
	}
	return ((void *)dst1);
}
