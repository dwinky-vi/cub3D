/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:47:25 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/15 16:46:08 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"
#include "head_parser.h"
#define ERROR09 "Error 09\n Found many players\n"
#define ERROR10 "Error 10\n Player not found\n"

void		ft_count_sprites(t_vars *vars)
{
	size_t	k;
	size_t	j;

	vars->count_sprites = 0;
	k = 0;
	while (vars->data.map[k])
	{
		j = 0;
		while (vars->data.map[k][j])
		{
			if (vars->data.map[k][j] == '2')
				(vars->count_sprites)++;
			j++;
		}
		k++;
	}
}


void		ft_init_person_pos(t_person *person, double z1, double z2, double z3, double z4)
{
	person->dir.x  = z1;
	person->dir.y = z2;
	person->plane.x = z3;
	person->plane.y = z4;
}

void		ft_find_person(t_person *person, t_data *data)
{
	size_t	k;
	size_t	j;
	char	f;

	f = (char)FALSE;
	k = 0;
	while (data->map[k])
	{
		j = 0;
		while (data->map[k][j])
		{
			if (ft_strchr("NSEW", data->map[k][j]))
			{
				person->pos.x = k + 0.5;
				person->pos.y = j + 0.5;
				person->speed_move = 0.08;
				person->speed_rot = 0.045;
				if (data->map[k][j] == 'N') // север
				{
					ft_init_person_pos(person, -1, 0, 0, 0.66);
					
				}
				else if (data->map[k][j] == 'S') // юг
				{
					person->dir.x = 1;
					person->dir.y = 0;
					person->plane.x = 0;
					person->plane.y = -0.66;
				}
				else if (data->map[k][j] == 'W')// запад
				{
					person->dir.x = 0;
					person->dir.y = -1;
					person->plane.x = -0.66;
					person->plane.y = 0;
				}
				else if (data->map[k][j] == 'E') // восток
				{
					person->dir.x = 0;
					person->dir.y = 1;
					person->plane.x = 0.66;
					person->plane.y = 0;
				}
				data->map[k][j] = '0';
				if (f == (char)TRUE)
				{
					data->error = ERROR09;
					return ;
				}
				f = (char)TRUE;
			}
			j++;
		}
		k++;
	}
	if (!f)
		data->error = ERROR10;
}
