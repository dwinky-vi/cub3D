/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_some_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 14:14:21 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/11 22:47:19 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

int		ft_puterror(char *str)
{
	ft_putendl_fd(str, 1);
	return (-1);
}

void	ft_print_map(char **map)
{
	int		k;
	int		j;

	if (map == NULL)
	{
		ft_putstr("Error in map\n");
		return ;
	}
	k = 0;
	while (map[k] != NULL)
	{
		j = 0;
		while (map[k][j])
		{
			ft_putchar(map[k][j]);
			j++;
		}
		ft_putchar('\n');
		k++;
	}
}
