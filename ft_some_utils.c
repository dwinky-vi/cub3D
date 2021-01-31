/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_some_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 14:14:21 by dwinky            #+#    #+#             */
/*   Updated: 2021/01/31 14:31:25 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	ft_lstprint_as_str(t_list **list)
{
	while (*list)
	{
		ft_putendl_fd((*list)->content, 1);
		*list = (*list)->next;
	}
}