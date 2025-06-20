/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktroude <ktroude@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:44:34 by ktroude           #+#    #+#             */
/*   Updated: 2021/11/02 13:53:16 by ktroude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_strlen_v2(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i1;
	int		i2;
	char	*str;

	if (!s1)
		return (NULL);
	i1 = ft_strlen_v2(s1);
	i2 = ft_strlen_v2(s2);
	str = malloc(sizeof(char) * (i1 + i2 + 1));
	if (!(str))
		return (NULL);
	i1 = 0;
	i2 = 0;
	while (s1[i1])
	{
		str[i1] = s1[i1];
		i1++;
	}
	while (s2[i2])
		str[i1++] = s2[i2++];
	str[i1] = 0;
	return (str);
}
