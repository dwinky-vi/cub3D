/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:29:38 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/03 18:07:28 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"
#include <math.h>

int			make_step(t_vars *vars)
{
	if (vars->k_13)
	{
		printf("%f,    %f\n", vars->person.posX, vars->person.posY);
		ft_putstr("13\n");
		if (vars->data.map[(int)(vars->person.posX + vars->person.dirX * vars->person.moveSpeed)][(int)vars->person.posY] == '0')
			vars->person.posX += vars->person.dirX * vars->person.moveSpeed;
		if (vars->data.map[(int)(vars->person.posX)][(int)(vars->person.posY + vars->person.dirY * vars->person.moveSpeed)] == '0')
			vars->person.posY += vars->person.dirY * vars->person.moveSpeed;
		printf("%f,    %f\n", vars->person.posX, vars->person.posY);
	}
	if (vars->k_1)
	{
		printf("%f,  %f,    %f\n", vars->person.posX, vars->person.posY, vars->person.dirX);
		ft_putstr("1\n");
		if (vars->data.map[(int)(vars->person.posX - vars->person.dirX * vars->person.moveSpeed)][(int)vars->person.posY] == '0')
			vars->person.posX -= vars->person.dirX * vars->person.moveSpeed;
      	if (vars->data.map[(int)vars->person.posX][(int)(vars->person.posY - vars->person.dirY * vars->person.moveSpeed)] == '0')
			vars->person.posY -= vars->person.dirY * vars->person.moveSpeed;
	}
	if (vars->k_0)
	{
		ft_putstr("0\n");
		//both camera direction and camera plane must be rotated
		double oldDirX = vars->person.dirX;
		vars->person.dirX = vars->person.dirX * cos(vars->person.rotSpeed) - vars->person.dirY * sin(vars->person.rotSpeed);
      	vars->person.dirY = oldDirX * sin(vars->person.rotSpeed) + vars->person.dirY * cos(vars->person.rotSpeed);
      	double oldPlaneX = vars->person.planeX;
      	vars->person.planeX = vars->person.planeX * cos(vars->person.rotSpeed) - vars->person.planeY * sin(vars->person.rotSpeed);
      	vars->person.planeY = oldPlaneX * sin(vars->person.rotSpeed) + vars->person.planeY * cos(vars->person.rotSpeed);
	}
	if (vars->k_2)
	{
		ft_putstr("2\n");
		//both camera direction and camera plane must be rotated
    	double oldDirX = vars->person.dirX;
    	vars->person.dirX = vars->person.dirX * cos(-vars->person.rotSpeed) - vars->person.dirY * sin(-vars->person.rotSpeed);
    	vars->person.dirY = oldDirX * sin(-vars->person.rotSpeed) + vars->person.dirY * cos(-vars->person.rotSpeed);
    	double oldPlaneX = vars->person.planeX;
    	vars->person.planeX = vars->person.planeX * cos(-vars->person.rotSpeed) - vars->person.planeY * sin(-vars->person.rotSpeed);
    	vars->person.planeY = oldPlaneX * sin(-vars->person.rotSpeed) + vars->person.planeY * cos(-vars->person.rotSpeed);
	}
	return (0);
}

int			key_press_hook(int key, t_vars *vars)
{
	if (key == 13)
		vars->k_13 = TRUE;
	if (key == 1)
		vars->k_1 = TRUE;
	if (key == 0)
		vars->k_0 = TRUE;
	if (key == 2)
		vars->k_2 = TRUE;
	return (0);
}

int			key_release_hook(int key, t_vars *vars)
{
	if (key == 53)
		exit(0);
	if (key == 13)
		vars->k_13 = FALSE;
	if (key == 1)
		vars->k_1 = FALSE;
	if (key == 0)
		vars->k_0 = FALSE;
	if (key == 2)
		vars->k_2 = FALSE;
	return (0);
}

static int	exit_hook(int key, void *vars)
{
	ft_putstr("Exit");
	exit(0);
}

//WALL CASTING
int ft_raycast(t_vars *vars)
{
	int w = vars->data.config.r.size_x;
	int h = vars->data.config.r.size_y;
	double posX = vars->person.posX;
	double posY = vars->person.posY;

	vars->img.img = mlx_new_image(vars->mlx_ptr, vars->data.config.r.size_x, vars->data.config.r.size_y);
    vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel, &vars->img.line_length, &vars->img.endian);
	make_step(vars);
	//start the main loop
    for (int x = 0; x < w; x++)
    {
		//calculate ray position and direction
		double cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
		double rayDirX = vars->person.dirX + vars->person.planeX * cameraX;
		double rayDirY = vars->person.dirY + vars->person.planeY * cameraX;

		//which box of the map we're in
		int mapX = (int)posX;
		int mapY = (int)posY;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		//   double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		//   double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;
 
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = FALSE; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}

		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			// hit удар луча об стену
			if (vars->data.map[mapX][mapY] == '1')
				hit = TRUE;
		}

		//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
		if (side == 0)
			perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(h / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		// drawStart начало стены
		// drawEnd конец стены
		int drawStart = -lineHeight / 2 + h / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if (drawEnd >= h)
			drawEnd = h - 1;
		int y = 0;
		while (y < vars->data.config.r.size_y)
		{
			if (y < drawStart) // потолок
			{
				my_mlx_pixel_put(&vars->img, x, y, vars->data.config.c_int);
			}
			else if (y > drawEnd) // пол
			{
				my_mlx_pixel_put(&vars->img, x, y, vars->data.config.f_int);
			}
			else // стена
			{
				my_mlx_pixel_put(&vars->img, x, y, 0xFFFFFF);
			}
			y++;
		}
	}
	// vars->person.posX = posX;
	// vars->person.posY = posY;
	mlx_hook(vars->win_ptr, 2, 0, key_press_hook, vars);
	mlx_hook(vars->win_ptr, 3, 0, key_release_hook, vars);
	mlx_hook(vars->win_ptr, 17, 0, exit_hook, vars);
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img.img, 0, 0);
	return (0);
}