/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:29:38 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/12 00:31:24 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

int		ft_raycast(t_vars *vars)
{
	int		w;
	int		h;
	double	pos_x;
	double	pos_y;
	int		tex_w = 64;
	int		tex_h = 64;
	double	perpendiculars_array[vars->data.config.width];

	if (ft_init_img(vars->mlx_ptr, &vars->img, &vars->data.config))
		return (-1);
	w = vars->data.config.width;
	h = vars->data.config.height;
	pos_x = vars->person.pos_x;
	pos_y = vars->person.pos_y;
	make_step(vars);
	int x = 0;
	while (x < w)
	{
		// cameraX [-1, 1] приведение значения ширины экрана к этим величинам 
		double cameraX = 2 * x / (double)w - 1;
		double rayDirX = vars->person.dirX + vars->person.planeX * cameraX;
		double rayDirY = vars->person.dirY + vars->person.planeY * cameraX;

		//which box of the map we're in
		int map_x = pos_x;
		int map_y = pos_y;

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
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (pos_x - map_x) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (map_x + 1.0 - pos_x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (pos_y - map_y) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (map_y + 1.0 - pos_y) * deltaDistY;
		}
		while (hit == FALSE)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				map_x += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				map_y += stepY;
				side = 1; // вертикаль
			}
			if (vars->data.map[map_x][map_y] == '1')
				hit = TRUE;
		}
		int color;
		//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
		if (side == 0)  //вертикаль
			perpWallDist = (map_x - pos_x + (1 - stepX) / 2) / rayDirX;
		else // горизанталь
			perpWallDist = (map_y - pos_y + (1 - stepY) / 2) / rayDirY;
		ft_get_tex_width_height(vars, &tex_w, &tex_h, side, stepX, stepY);
		int lineHeight = (int)(h / perpWallDist);
		// drawStart начало стены
		// drawEnd конец стены
		int drawStart = -lineHeight / 2 + h / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if (drawEnd >= h)
			drawEnd = h - 1;
		int y = 0;
	/********/
			//texturing calculations
		int texNum = vars->data.map[map_x][map_y] - 1; //1 subtracted from it so that texture 0 can be used!

		// это y-координата стены, если side == 1
		double wallX; 
		if (side == 0)
			wallX = pos_y + perpWallDist * rayDirY;
		else
			wallX = pos_x + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		// texX –– x-координата текстуры
		int texX = (int)(wallX * (double)tex_w);
		if (side == 0 && rayDirX > 0)
			texX = tex_w - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = tex_w - texX - 1;
			// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * tex_h / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - h / 2 + lineHeight / 2) * step;
	/********/
		while (y < vars->data.config.height)
		{
			if (y < drawStart) // потолок
				my_mlx_pixel_put(&vars->img, x, y, vars->data.config.c_int);
			else if (y > drawEnd) // пол
				my_mlx_pixel_put(&vars->img, x, y, vars->data.config.f_int);
			else // стена
			{
				int texY = (int)texPos & (tex_h - 1);
				texPos += step;
				color = get_color_wall(vars, texX, texY, stepX, stepY, side);
				my_mlx_pixel_put(&vars->img, x, y, color);
			}
			y++;
		}
		perpendiculars_array[x] = perpWallDist;
		x++;
	}
	ft_spritecasting(vars, pos_x, pos_y, perpendiculars_array);
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img.img, 0, 0);
	mlx_destroy_image(vars->mlx_ptr, vars->img.img);
	return (0);
}

int		get_color_wall(t_vars *vars, double texX, double texY, int stepX, int stepY, int side)
{
	int color;

	if (side == 0 && stepX == -1)
		color = ft_mlx_get_color(&vars->texture[0], texX, texY);
	else if (side == 0 && stepX == 1)
		color = ft_mlx_get_color(&vars->texture[1], texX, texY);
	else if (stepY == -1)
		color = ft_mlx_get_color(&vars->texture[2], texX, texY);
	else if (stepY == 1)
		color = ft_mlx_get_color(&vars->texture[3], texX, texY);
	return (color);
}

void	ft_get_tex_width_height(t_vars *vars, int *tex_w, int *tex_h, int side, int stepX, int stepY)
{
	if (side == 0 && stepX == -1)
	{
		*tex_h = vars->texture[0].height;
		*tex_w = vars->texture[0].width;
	}
	else if (side == 0 && stepX == 1)
	{
		*tex_h = vars->texture[1].height;
		*tex_w = vars->texture[1].width;
	}
	else if (stepY == -1)
	{
		*tex_h = vars->texture[2].height;
		*tex_w = vars->texture[2].width;
	}
	else if (stepY == 1)
	{
		*tex_h = vars->texture[3].height;
		*tex_w = vars->texture[3].width;
	}
}
