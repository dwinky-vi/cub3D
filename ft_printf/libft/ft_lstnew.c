/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 20:31:46 by dwinky            #+#    #+#             */
/*   Updated: 2020/11/03 18:58:14 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *new_content)
{
	t_list *new_node;

	new_node = (t_list *)ft_calloc(1, sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node->content = new_content;
	new_node->next = NULL;
	return (new_node);
}
