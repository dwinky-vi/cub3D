/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_some_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 14:14:21 by dwinky            #+#    #+#             */
/*   Updated: 2021/01/31 20:58:22 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		ft_puterror(char *str)
{
	ft_putendl_fd(error, 1);
	return (-1);
}
void	ft_lstprint_ass_str(t_list **list)
{
	if (list == NULL)
	{
		ft_printf("Error in list\n");
		return ;
	}
	while (*list)
	{
		ft_putendl_fd((*list)->content, 1);
		*list = (*list)->next;
	}
}

void	ft_print_map(char **map)
{
	int		k;

	k = -1;
	if (map == NULL)
	{
		ft_printf("Error in map\n");
		return ;
	}
	while (map[++k])
	{
		ft_putstr(map[k]);
		if (map[k + 1] != NULL)
			ft_putchar('\n');
	}
}

void	ft_print_config(t_config config)
{
	ft_printf("R_1 = <%d>\n", config.r.size_x);
	ft_printf("R_2 = <%d>\n", config.r.size_y);
	ft_printf("NO = <%s>\n", config.no);
	ft_printf("SO = <%s>\n", config.so);
	ft_printf("WE = <%s>\n", config.we);
	ft_printf("EA = <%s>\n", config.ea);
	ft_printf("S = <%s>\n", config.s);
	ft_printf("F = <%s>\n", config.f);
	ft_printf("C = <%s>\n", config.c);
}