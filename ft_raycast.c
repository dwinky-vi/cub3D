/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:29:38 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/04 10:32:19 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

int ft_raycast(t_vars *vars)
{
	int w = vars->data.config.r.width;
	int h = vars->data.config.r.height;
	double posX = vars->person.posX;
	double posY = vars->person.posY;

	vars->img.img = mlx_new_image(vars->mlx_ptr, vars->data.config.r.width, vars->data.config.r.height);
    vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel, &vars->img.line_length, &vars->img.endian);
	make_step(vars);
	int x = 0;
	while (x < w)
    {
		// cameraX [-1, 1] приведение значения ширины экрана к этим величинам 
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
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;
 
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = FALSE; //was there a wall hit?
		int side; // вертикальная или горизонтальная стена на карте

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
				side = 1; // вертикаль
			}
			//Check if ray has hit a wall
			// hit это удар луча об стену
			if (vars->data.map[mapX][mapY] == '1')
				hit = TRUE;
		}
		int color;
		//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
		if (side == 0) //вертикаль
		{
			perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
			if (stepX == -1)
			{
				color = 0x0000CD; // синий
			}
			else if (stepX == 1)
			{
				color = 0x8A2BE2; // фиолетовый
			}
		}
		else // горизанталь
		{
			perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
			if (stepY == -1)
			{
				color = 0x00FF7F;
			}
			else if (stepY == 1)
			{
				color = 0xFFD700; // жёлтый
			}
		}

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
		while (y < vars->data.config.r.height)
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
				my_mlx_pixel_put(&vars->img, x, y, color);
			}
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img.img, 0, 0);
	mlx_destroy_image(vars->mlx_ptr,vars->img.img);
	return (0);
}