/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_steps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:58:22 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/12 04:32:23 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"
#define KEY_W k_13
#define KEY_S k_1
#define KEY_A k_0
#define KEY_D k_2
#define KEY_LEFT k_123
#define KEY_RIGHT k_124
#define KEY_ESC k_257

void		make_step_forward(char **map, t_person *person, float speed)
{
	if (map[(int)(person->pos.x + person->dir.x * person->moveSpeed * speed)][(int)person->pos.y] == '0')
		person->pos.x += person->dir.x * person->moveSpeed * speed;
	if (map[(int)(person->pos.x)][(int)(person->pos.y + person->dir.y * person->moveSpeed * speed)] == '0')
		person->pos.y += person->dir.y * person->moveSpeed * speed;
}

void		make_step_back(char **map, t_person *person)
{
	if (map[(int)(person->pos.x - person->dir.x * person->moveSpeed)][(int)person->pos.y] == '0')
		person->pos.x -= person->dir.x * person->moveSpeed;
	if (map[(int)person->pos.x][(int)(person->pos.y - person->dir.y * person->moveSpeed)] == '0')
		person->pos.y -= person->dir.y * person->moveSpeed;
}

void		make_step_left(char **map, t_person *person)
{
	if (map[(int)(person->pos.x - person->plane.x * person->moveSpeed)][(int)person->pos.y] == '0')
		person->pos.x -= person->plane.x * person->moveSpeed;
	if (map[(int)(person->pos.x)][(int)(person->pos.y - person->plane.y * person->moveSpeed)] == '0')
		person->pos.y -= person->plane.y * person->moveSpeed;
}

void		make_step_right(char **map, t_person *person)
{
	if (map[(int)(person->pos.x + person->plane.x * person->moveSpeed)][(int)person->pos.y] == '0')
		person->pos.x += person->plane.x * person->moveSpeed;
	if (map[(int)(person->pos.x)][(int)(person->pos.y + person->plane.y * person->moveSpeed)] == '0')
		person->pos.y += person->plane.y * person->moveSpeed;
}

void		make_rotation_left(char **map, t_person *person)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = person->dir.x;
	old_plane_x = person->plane.x;
	person->dir.x = person->dir.x * cos(person->rotSpeed) - person->dir.y * sin(person->rotSpeed);
	person->dir.y = old_dir_x * sin(person->rotSpeed) + person->dir.y * cos(person->rotSpeed);
	person->plane.x = person->plane.x * cos(person->rotSpeed) - person->plane.y * sin(person->rotSpeed);
	person->plane.y = old_plane_x * sin(person->rotSpeed) + person->plane.y * cos(person->rotSpeed);
}

void		make_rotation_right(char **map, t_person *person)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = person->dir.x;
	old_plane_x = person->plane.x;
	person->dir.x = person->dir.x * cos(-person->rotSpeed) - person->dir.y * sin(-person->rotSpeed);
	person->dir.y = old_dir_x * sin(-person->rotSpeed) + person->dir.y * cos(-person->rotSpeed);
	person->plane.x = person->plane.x * cos(-person->rotSpeed) - person->plane.y * sin(-person->rotSpeed);
	person->plane.y = old_plane_x * sin(-person->rotSpeed) + person->plane.y * cos(-person->rotSpeed);
}

int			make_step(t_vars *vars)
{
	if (vars->KEY_W)
		make_step_forward(vars->data.map, &vars->person, vars->KEY_ESC ? 2.8 : 1);
	if (vars->KEY_S)
		make_step_back(vars->data.map, &vars->person);
	if (vars->KEY_A)
		make_step_left(vars->data.map, &vars->person);
	if (vars->KEY_D)
		make_step_right(vars->data.map, &vars->person);
	if (vars->KEY_LEFT)
		make_rotation_left(vars->data.map, &vars->person);
	if (vars->KEY_RIGHT)
		make_rotation_right(vars->data.map, &vars->person);
	return (0);
}
