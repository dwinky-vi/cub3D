/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:47:25 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/18 02:32:12 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"
#define ERROR09 "Error\n09 Found many players\n"
#define ERROR10 "Error\n10 Player not found\n"

static void	ft_init_person_dir(t_person *person, double z1, double z2)
{
	person->dir.x = z1;
	person->dir.y = z2;
}

static void	ft_init_person_plane(t_person *person, double z3, double z4)
{
	person->plane.x = z3;
	person->plane.y = z4;
}

static void	ft_init_person_pos_dir_plane(t_person *person, t_data *data,
															size_t k, size_t j)
{
	person->pos.x = k + 0.5;
	person->pos.y = j + 0.5;
	person->speed_move = 0.08;
	person->speed_rot = 0.04;
	if (data->map[k][j] == 'N')
	{
		ft_init_person_dir(person, -1, 0);
		ft_init_person_plane(person, 0, 0.66);
	}
	else if (data->map[k][j] == 'S')
	{
		ft_init_person_dir(person, 1, 0);
		ft_init_person_plane(person, 0, -0.66);
	}
	else if (data->map[k][j] == 'W')
	{
		ft_init_person_dir(person, 0, -1);
		ft_init_person_plane(person, -0.66, 0);
	}
	else if (data->map[k][j] == 'E')
	{
		ft_init_person_dir(person, 0, 1);
		ft_init_person_plane(person, 0.66, 0);
	}
	data->map[k][j] = '0';
}

/*
** North север
** South юг
** West запад
** East восток
*/

void		ft_find_person(t_person *person, t_data *data)
{
	size_t	k;
	size_t	j;
	char	f;

	f = (char)FALSE;
	k = -1;
	while (data->map[++k])
	{
		j = -1;
		while (data->map[k][++j])
		{
			if (ft_strchr("NSEW", data->map[k][j]))
			{
				ft_init_person_pos_dir_plane(person, data, k, j);
				if (f == (char)TRUE)
				{
					data->error = ERROR09;
					return ;
				}
				f = (char)TRUE;
			}
		}
	}
	if (!f)
		data->error = ERROR10;
}

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
