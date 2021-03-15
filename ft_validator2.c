/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validator2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 22:05:44 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/15 19:20:36 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

int		ft_check_other_chars_map(char **map)
{
	size_t	k;
	size_t	j;

	k = 0;
	while (map[k])
	{
		j = 0;
		if (map[k][0] == '\n')
		{
			return (1);
		}
			ft_putnbr(k);
			ft_putchar('\n');
		while (map[k][j])
		{
			if (!(ft_strchr("012 \nNSWE", map[k][j])))
				return (1);
			if (map[k][j] == '\n' && map[k][j + 1] == ' ')
				return (1);
			j++;
		}
		k++;
	}
	return (0);
}

// int		ft_check_spaces_new_lines(char **make_step)
// {
// 	size_t	k;
// 	size_t	j;
// }