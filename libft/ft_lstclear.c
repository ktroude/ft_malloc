/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktroude <ktroude@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 16:54:43 by ktroude           #+#    #+#             */
/*   Updated: 2021/11/02 13:56:25 by ktroude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*t;

	if (!(del || lst || *lst))
		return ;
	while (lst && *lst)
	{
		t = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = t;
	}
}
