/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:42:19 by dwinky            #+#    #+#             */
/*   Updated: 2020/11/03 16:42:20 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new_node)
{
	if (lst == NULL || new_node == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new_node;
		return ;
	}
	new_node->next = *lst;
	*lst = new_node;
}
