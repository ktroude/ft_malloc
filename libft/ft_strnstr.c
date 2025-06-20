/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktroude <ktroude@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:00:20 by ktroude           #+#    #+#             */
/*   Updated: 2021/11/01 16:24:55 by ktroude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	i2;
	size_t	size;

	i = 0;
	size = ft_strlen(needle);
	if (size == 0 || needle == haystack)
		return ((char *)haystack);
	while (haystack[i])
	{
		i2 = 0;
		while (haystack[i] == needle[i2] && i < len && haystack[i])
		{
			i++;
			i2++;
			if (i2 == size)
				return ((char *) &haystack[i - i2]);
		}
		i = i - i2;
		i++;
	}
	return (NULL);
}
