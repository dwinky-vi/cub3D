/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validator2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 22:05:44 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/15 22:09:28 by dwinky           ###   ########.fr       */
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
		while (map[k][j])
		{
			if (!(ft_strchr("012 \nNSWE", map[k][j])))
			{
				ft_putchar(map[k][j - 1]);
				return (1);
			}
			// if (map[k][j] == '\n' && map[k][j + 1] == ' ')
			// 	return (1);
			j++;
		}
		k++;
	}
	return (0);
}

int ft_check_empty_line_map(char **map)
{
	size_t	k;

	k = 0;
	while (map[k])
	{
		if (map[k][0] == '\0')
			return (1);
		k++;
	}
	return (0);
}
// int		ft_check_spaces_new_lines(char **make_step)
// {
// 	size_t	k;
// 	size_t	j;
// }

// в карте не может быть пустых строк