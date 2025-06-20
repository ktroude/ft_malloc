/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktroude <ktroude@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:12:41 by ktroude           #+#    #+#             */
/*   Updated: 2021/11/02 13:54:11 by ktroude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_finder1(char const *s1, char const *set)
{
	int	i1;
	int	i2;

	if (set == 0)
		return (0);
	i1 = 0;
	i2 = 0;
	while (s1[i1])
	{
		while (set[i2])
		{
			if (set[i2] == s1[i1])
				break ;
			if (set[i2 + 1] == 0 && set[i2] != s1[i1])
				return (i1);
			i2++;
		}
		i2 = 0;
		i1++;
	}
	return (0);
}

static int	ft_check_s1_set_diff(char const *s1, char const *set)
{
	int	i;
	int	i2;
	int	secu;

	i = 0;
	i2 = 0;
	secu = 0;
	while (s1[i])
	{
		while (set[i2])
		{
			if (set[i2] == s1[i])
			{
				secu++;
				break ;
			}
			i2++;
		}
		i2 = 0;
		i++;
	}
	if ((size_t)secu == ft_strlen(s1))
		return (1);
	else
		return (0);
}

static int	ft_finder2(char const *s1, char const *set)
{
	int	i1;
	int	i2;

	i1 = ft_strlen(s1) - 1;
	i2 = 0;
	while (i1 != 0)
	{
		while (set[i2])
		{
			if (set[i2] == s1[i1])
				break ;
			if (set[i2 + 1] == 0 && set[i2] != s1[i1])
				return (i1 + 1);
			i2++;
		}
		i2 = 0;
		i1--;
	}
	return (ft_strlen(s1) - 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i1;
	int		i2;
	int		j;
	char	*str;

	if (!s1)
		return (NULL);
	j = 0;
	i1 = ft_finder1(s1, set);
	i2 = ft_finder2(s1, set);
	if (ft_check_s1_set_diff(s1, set) == 1)
	{
		str = malloc(sizeof(char));
		str[0] = 0;
		return (str);
	}
	str = malloc(sizeof(char) * (i2 - i1) + 1);
	if (str == 0)
		return (NULL);
	while (i1 < i2)
		str[j++] = s1[i1++];
	if (ft_strlen(set) == 0)
		str[j++] = s1[i2];
	str[j] = '\0';
	return (str);
}
