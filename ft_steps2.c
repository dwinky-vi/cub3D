/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_steps2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 20:28:13 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/12 20:30:49 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

void		make_rotation_left(char **map, t_person *p)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = p->dir.x;
	old_plane_x = p->plane.x;
	p->dir.x = p->dir.x * cos(p->speed_rot) - p->dir.y * sin(p->speed_rot);
	p->dir.y = old_dir_x * sin(p->speed_rot) + p->dir.y * cos(p->speed_rot);
	p->plane.x = p->plane.x * cos(p->speed_rot) - p->plane.y *
															sin(p->speed_rot);
	p->plane.y = old_plane_x * sin(p->speed_rot) + p->plane.y *
															cos(p->speed_rot);
}

void		make_rotation_right(char **map, t_person *p)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = p->dir.x;
	old_plane_x = p->plane.x;
	p->dir.x = p->dir.x * cos(-p->speed_rot) - p->dir.y * sin(-p->speed_rot);
	p->dir.y = old_dir_x * sin(-p->speed_rot) + p->dir.y * cos(-p->speed_rot);
	p->plane.x = p->plane.x * cos(-p->speed_rot) - p->plane.y *
															sin(-p->speed_rot);
	p->plane.y = old_plane_x * sin(-p->speed_rot) + p->plane.y *
															cos(-p->speed_rot);
}
