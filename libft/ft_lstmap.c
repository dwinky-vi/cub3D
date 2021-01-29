/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:45:40 by dwinky            #+#    #+#             */
/*   Updated: 2020/11/03 19:10:40 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*cur_lst;
	t_list	*head;

	if (lst == NULL || f == NULL)
		return (NULL);
	head = ft_lstnew((*f)(lst->content));
	new_lst = head;
	if (head == NULL)
		return (NULL);
	lst = lst->next;
	while (lst != NULL)
	{
		cur_lst = ft_lstnew((*f)(lst->content));
		if (cur_lst == NULL)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		new_lst->next = cur_lst;
		new_lst = new_lst->next;
		lst = lst->next;
	}
	return (head);
}
