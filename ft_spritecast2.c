/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spritecasting2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 15:28:00 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/14 16:51:18 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

static double	pow_2(double num)
{
	return (num * num);
}

void			ft_calculate_sprites(t_sprite *sp, char **map, t_point_d *pos)
{
	int k;
	int j;
	int i;

	i = 0;
	k = 0;
	while (map[k])
	{
		j = 0;
		while (map[k][j])
		{
			if (map[k][j] == '2')
			{
				sp[i].x = k + 0.5;
				sp[i].y = j + 0.5;
				sp[i].distance = pow_2(pos->x - sp[i].x);
				sp[i].distance += pow_2(pos->y - sp[i].y);
				i++;
			}
			j++;
		}
		k++;
	}
}
