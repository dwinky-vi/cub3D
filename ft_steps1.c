/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_steps1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:58:22 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/18 06:12:34 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"
#define KEY_W k_13
#define KEY_S k_1
#define KEY_A k_0
#define KEY_D k_2
#define KEY_LEFT k_123
#define KEY_RIGHT k_124
#define SHIFT k_257

void		make_step_forward(char **map, t_person *person, float speed)
{
	int x;
	int y;

	x = person->pos.x + person->dir.x * person->speed_move * speed;
	y = person->pos.y;
	if (map[x][y] == '0')
		person->pos.x += person->dir.x * person->speed_move * speed;
	x = person->pos.x;
	y = person->pos.y + person->dir.y * person->speed_move * speed;
	if (map[x][y] == '0')
		person->pos.y += person->dir.y * person->speed_move * speed;
}

void		make_step_back(char **map, t_person *person, float speed)
{
	int x;
	int y;

	x = person->pos.x - person->dir.x * person->speed_move * speed;
	y = person->pos.y;
	if (map[x][y] == '0')
		person->pos.x -= person->dir.x * person->speed_move * speed;
	x = person->pos.x;
	y = person->pos.y - person->dir.y * person->speed_move * speed;
	if (map[x][y] == '0')
		person->pos.y -= person->dir.y * person->speed_move * speed;
}

void		make_step_left(char **map, t_person *person)
{
	int x;
	int y;

	x = person->pos.x - person->plane.x * person->speed_move;
	y = person->pos.y;
	if (map[x][y] == '0')
		person->pos.x -= person->plane.x * person->speed_move;
	x = person->pos.x;
	y = person->pos.y - person->plane.y * person->speed_move;
	if (map[x][y] == '0')
		person->pos.y -= person->plane.y * person->speed_move;
}

void		make_step_right(char **map, t_person *person)
{
	int x;
	int y;

	x = person->pos.x + person->plane.x * person->speed_move;
	y = person->pos.y;
	if (map[x][y] == '0')
		person->pos.x += person->plane.x * person->speed_move;
	x = person->pos.x;
	y = person->pos.y + person->plane.y * person->speed_move;
	if (map[x][y] == '0')
		person->pos.y += person->plane.y * person->speed_move;
}

int			make_step(t_vars *vars)
{
	if (vars->KEY_W)
		make_step_forward(vars->data.map, &vars->person, vars->SHIFT ? 3 : 1);
	if (vars->KEY_S)
		make_step_back(vars->data.map, &vars->person, vars->SHIFT ? 3 : 1);
	if (vars->KEY_A)
		make_step_left(vars->data.map, &vars->person);
	if (vars->KEY_D)
		make_step_right(vars->data.map, &vars->person);
	if (vars->KEY_LEFT)
		make_rotation_left(&vars->person);
	if (vars->KEY_RIGHT)
		make_rotation_right(&vars->person);
	return (0);
}
