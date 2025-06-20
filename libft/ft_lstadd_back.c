/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktroude <ktroude@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 16:54:02 by ktroude           #+#    #+#             */
/*   Updated: 2021/11/02 11:51:58 by ktroude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*lst;

	if (!new)
		return ;
	if (*alst)
	{
		lst = ft_lstlast(*alst);
		lst->next = new;
	}
	else
		*alst = new;
}
