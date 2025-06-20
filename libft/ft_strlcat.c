/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktroude <ktroude@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:18:15 by ktroude           #+#    #+#             */
/*   Updated: 2021/11/01 16:23:56 by ktroude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	i2;
	size_t	dst_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	i2 = 0;
	i = ft_strlen(dst);
	if (dst_len < dstsize - 1 && dstsize > 0)
	{
		while (dst_len + i2 < dstsize - 1 && src[i2])
		{
			dst[i] = src[i2];
			i++;
			i2++;
		}
		dst[i] = 0;
	}
	if (dstsize < dst_len)
		return (dstsize + src_len);
	return (dst_len + src_len);
}
