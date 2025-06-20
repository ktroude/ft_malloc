/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktroude <ktroude@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 11:32:34 by ktroude           #+#    #+#             */
/*   Updated: 2021/11/08 12:13:30 by ktroude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_malloc_error(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static int	ft_count_line_tab(char const *s, char c)
{
	int	i;
	int	secu;
	int	count;

	i = 0;
	secu = 0;
	count = 0;
	while ((size_t)i < ft_strlen(s))
	{
		if (s[i] == c)
			secu = 0;
		else if (!secu)
		{
			secu = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static void	ft_get_next_str(char **next_str, unsigned int *next_str_len, char c)
{
	unsigned int	i;

	*next_str += *next_str_len;
	*next_str_len = 0;
	i = 0;
	while (**next_str && **next_str == c)
		(*next_str)++;
	while ((*next_str)[i])
	{
		if ((*next_str)[i] == c)
			return ;
		(*next_str_len)++;
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char			**tab;
	char			*next_str;
	unsigned int	n_slen;
	unsigned int	count;
	unsigned int	i;

	if (!s)
		return (NULL);
	n_slen = 0;
	i = 0;
	count = ft_count_line_tab(s, c);
	tab = (char **)malloc(sizeof(char *) * (count + 1));
	if (!(tab))
		return (NULL);
	next_str = (char *)s;
	while (i < count)
	{
		ft_get_next_str(&next_str, &n_slen, c);
		tab[i] = (char *)malloc(sizeof(char) * (n_slen + 1));
		if (!(tab[i]))
			return (ft_malloc_error(tab));
		ft_strlcpy(tab[i++], next_str, n_slen + 1);
	}
	tab[i] = NULL;
	return (tab);
}
