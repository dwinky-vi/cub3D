/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:42:06 by dwinky            #+#    #+#             */
/*   Updated: 2020/11/03 16:42:09 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_node)
{
	if (lst != NULL && new_node != NULL)
	{
		if (*lst == NULL)
			*lst = new_node;
		else
			(ft_lstlast(*lst))->next = new_node;
	}
}
