/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:29:38 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/09 22:39:50 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

static int	ft_init_img(void *mlx_ptr, t_img *img, t_config *config)
{
	img->img = mlx_new_image(mlx_ptr, config->width, config->height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
									&img->line_length, &img->endian);
	if (img->addr == NULL)
		return (1);
	return (0);
}

int		ft_raycast(t_vars *vars)
{
	int		w = vars->data.config.width;
	int		h = vars->data.config.height;
	double	pos_x = vars->person.pos_x;
	double	pos_y = vars->person.pos_y;
	int		texWidth = 64;
	int		texHeight = 64;
	double	perpendiculars_array[vars->data.config.width];
	int		texture[8][texWidth * texHeight];

	if (ft_init_img(vars->mlx_ptr, &vars->img, &vars->data.config))
		return (-1);
	make_step(vars);
	generete_textures(texWidth, texHeight, texture);
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
		if (side == 0 && stepX == -1)
		{
			texHeight = vars->texture[0].height;
			texWidth = vars->texture[0].width;
		}
		else if (side == 0 && stepX == 1)
		{
			texHeight = vars->texture[1].height;
			texWidth = vars->texture[1].width;
		}
		else if (stepY == -1)
		{
			texHeight = vars->texture[2].height;
			texWidth = vars->texture[2].width;
		}
		else if (stepY == 1)
		{
			texHeight = vars->texture[3].height;
			texWidth = vars->texture[3].width;
		}
		//Calculate height of line to draw on screen
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
		int texX = (int)(wallX * (double)texWidth);
		if (side == 0 && rayDirX > 0)
			texX = texWidth - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = texWidth - texX - 1;
			// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * texHeight / lineHeight;
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
				int texY = (int)texPos & (texHeight - 1);
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

	if (side == 0) //вертикаль
	{
		if (stepX == -1)
			color = ft_mlx_get_color(&vars->texture[0], texX, texY);
		else if (stepX == 1)
			color = ft_mlx_get_color(&vars->texture[1], texX, texY);
	}
	else // горизанталь
	{
		if (stepY == -1)
			color = ft_mlx_get_color(&vars->texture[2], texX, texY);
		else if (stepY == 1)
			color = ft_mlx_get_color(&vars->texture[3], texX, texY);
	}
	return (color);
}

void	generete_textures(int texWidth, int texHeight, int texture[8][texWidth * texHeight])
{
	int x;
	int y;
	int xorcolor;
	int ycolor;
	int xycolor;

	x = 0;
	while (x < texWidth)
	{
		y = 0;
		while (y < texHeight)
		{
			xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
			ycolor = y * 256 / texHeight;
			xycolor = y * 128 / texHeight + x * 128 / texWidth;
			texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); //flat red texture with black cross
			texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
			texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			texture[4][texWidth * y + x] = 256 * xorcolor; //xor green
			texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
			texture[6][texWidth * y + x] = 65536 * ycolor; //red gradient
			texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
			y++;
		}
		x++;
	}
}