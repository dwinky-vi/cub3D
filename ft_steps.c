/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_steps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:58:22 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/04 10:32:19 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"
#define KEY_W k_13
#define KEY_S k_1
#define KEY_A k_0
#define KEY_D k_2

void		make_step_forward(char **map, t_person *person, int speed)
{
	if (map[(int)(person->posX + person->dirX * person->moveSpeed * speed)][(int)person->posY] == '0')
			person->posX += person->dirX * person->moveSpeed * speed;
	if (map[(int)(person->posX)][(int)(person->posY + person->dirY * person->moveSpeed * speed)] == '0')
		person->posY += person->dirY * person->moveSpeed * speed;
}

void		make_step_back(char **map, t_person *person)
{
	if (map[(int)(person->posX - person->dirX * person->moveSpeed)][(int)person->posY] == '0')
			person->posX -= person->dirX * person->moveSpeed;
	if (map[(int)person->posX][(int)(person->posY - person->dirY * person->moveSpeed)] == '0')
		person->posY -= person->dirY * person->moveSpeed;
}

void		make_step_left(char **map, t_person *person)
{
	if (map[(int)(person->posX - person->planeX * person->moveSpeed)][(int)person->posY] == '0')
			person->posX -= person->planeX * person->moveSpeed;
	if (map[(int)(person->posX)][(int)(person->posY - person->planeY * person->moveSpeed)] == '0')
			person->posY -= person->planeY * person->moveSpeed;
}

void		make_step_right(char **map, t_person *person)
{
	if (map[(int)(person->posX + person->planeX * person->moveSpeed)][(int)person->posY] == '0')
			person->posX += person->planeX * person->moveSpeed;
	if (map[(int)(person->posX)][(int)(person->posY + person->planeY * person->moveSpeed)] == '0')
		person->posY += person->planeY * person->moveSpeed;
}

void		make_rotation_left(char **map, t_person *person)
{
	double oldDirX;
	double oldPlaneX;

	oldDirX = person->dirX;
	oldPlaneX = person->planeX;
	person->dirX = person->dirX * cos(person->rotSpeed) - person->dirY * sin(person->rotSpeed);
	person->dirY = oldDirX * sin(person->rotSpeed) + person->dirY * cos(person->rotSpeed);
	person->planeX = person->planeX * cos(person->rotSpeed) - person->planeY * sin(person->rotSpeed);
	person->planeY = oldPlaneX * sin(person->rotSpeed) + person->planeY * cos(person->rotSpeed);
}

void		make_rotation_right(char **map, t_person *person)
{
	double oldDirX;
	double oldPlaneX;

	oldDirX = person->dirX;
	oldPlaneX = person->planeX;
	person->dirX = person->dirX * cos(-person->rotSpeed) - person->dirY * sin(-person->rotSpeed);
	person->dirY = oldDirX * sin(-person->rotSpeed) + person->dirY * cos(-person->rotSpeed);
	person->planeX = person->planeX * cos(-person->rotSpeed) - person->planeY * sin(-person->rotSpeed);
	person->planeY = oldPlaneX * sin(-person->rotSpeed) + person->planeY * cos(-person->rotSpeed);
}

int			make_step(t_vars *vars)
{
	if (vars->KEY_W)
	{
		// if (vars->k_123)
		// 	make_rotation_left(vars->data.map, &vars->person);
		// if (vars->k_124)
		// 	make_rotation_right(vars->data.map, &vars->person);
		make_step_forward(vars->data.map, &vars->person, vars->k_257 ? 2 : 1);
	}
	if (vars->KEY_S)
	{
		// if (vars->k_123)
		// 	make_rotation_left(vars->data.map, &vars->person);
		// if (vars->k_124)
		// 	make_rotation_right(vars->data.map, &vars->person);
		make_step_back(vars->data.map, &vars->person);
	}
	if (vars->KEY_A)
		make_step_left(vars->data.map, &vars->person);
	if (vars->KEY_D)
		make_step_right(vars->data.map, &vars->person);
	if (vars->k_123)
		make_rotation_left(vars->data.map, &vars->person);
	if (vars->k_124)
		make_rotation_right(vars->data.map, &vars->person);
	return (0);
}
