/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktroude <ktroude@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:58:16 by ktroude           #+#    #+#             */
/*   Updated: 2021/10/26 14:22:43 by ktroude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dst1;
	char	*src2;

	dst1 = (char *)dst;
	src2 = (char *)src;
	if (n == 0)
		return (dst);
	if (!dst && !src)
		return (0);
	while (n--)
		dst1[n] = src2[n];
	return ((void *)dst1);
}
