/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:29:38 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/04 21:10:18 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

//sort algorithm
//sort the sprites based on distance
// void sortSprites(int* order, double* dist, int amount)
// {
// 	// std::vector<std::pair<double, int>> sprites(amount);
// 	for(int i = 0; i < amount; i++)
// 	{
// 		sprites[i].first = dist[i];
// 		sprites[i].second = order[i];
// 	}
// 	std::sort(sprites.begin(), sprites.end());
// 	// restore in reverse order to go from farthest to nearest
// 	for(int i = 0; i < amount; i++)
// 	{
// 		dist[i] = sprites[amount - i - 1].first;
// 		order[i] = sprites[amount - i - 1].second;
// 	}
// }

unsigned int	ft_get_color_2(t_texture *data, int x, int y)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

//function used to sort the sprites
void sortSprites(int *order, double *dist, int amount);

int ft_raycast(t_vars *vars)
{
	int		w = vars->data.config.width;
	int		h = vars->data.config.height;
	double	posX = vars->person.posX;
	double	posY = vars->person.posY;
	int		texWidth = 64;
	int 	texHeight = 64;
	double	ZBuffer[vars->data.config.width];

	vars->img.img = mlx_new_image(vars->mlx_ptr, vars->data.config.width, vars->data.config.height);
    vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel, &vars->img.line_length, &vars->img.endian);
	make_step(vars);

	//generate some textures
	int texture[8][texWidth * texHeight];
	for (int x = 0; x < texWidth; x++)
		for (int y = 0; y < texHeight; y++)
		{
			int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
			int ycolor = y * 256 / texHeight;
			int xycolor = y * 128 / texHeight + x * 128 / texWidth;
			texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); //flat red texture with black cross
			texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
			texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			texture[4][texWidth * y + x] = 256 * xorcolor; //xor green
			texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
			texture[6][texWidth * y + x] = 65536 * ycolor; //red gradient
			texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
		}
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
		while (hit == FALSE)
		{
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
				texHeight = vars->texture[0].height;
				texWidth = vars->texture[0].width;
			}
			else if (stepX == 1)
			{
				texHeight = vars->texture[1].height;
				texWidth = vars->texture[1].width;
			}
		}
		else // горизанталь
		{
			perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
			if (stepY == -1)
			{
				texHeight = vars->texture[2].height;
				texWidth = vars->texture[2].width;
			}
			else if (stepY == 1)
			{
				texHeight = vars->texture[3].height;
				texWidth = vars->texture[3].width;
			}
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
		int texNum = vars->data.map[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

		// это y-координата стены, если side == 1
		double wallX; 
		if (side == 0)
			wallX = posY + perpWallDist * rayDirY;
		else
			wallX = posX + perpWallDist * rayDirX;
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
				if (side == 0) //вертикаль
				{

					if (stepX == -1)
						 color = ft_get_color_2(&vars->texture[0], texX, texY);
					else if (stepX == 1)
						 color = ft_get_color_2(&vars->texture[1], texX, texY);
				}
				else // горизанталь
				{
					if (stepY == -1)
						 color = ft_get_color_2(&vars->texture[2], texX, texY);
					else if (stepY == 1)
						 color = ft_get_color_2(&vars->texture[3], texX, texY);
				}
				my_mlx_pixel_put(&vars->img, x, y, color);
			}
			if (cameraX == 0 && y == h / 2)
			{
				my_mlx_pixel_put(&vars->img, x, y, 0xFFFFFF);
				my_mlx_pixel_put(&vars->img, x, y + 1, 0xFFFFFF);
				my_mlx_pixel_put(&vars->img, x, y + 2, 0xFFFFFF);
				my_mlx_pixel_put(&vars->img, x + 1, y, 0xFFFFFF);
				my_mlx_pixel_put(&vars->img, x + 1, y + 1, 0xFFFFFF);
				my_mlx_pixel_put(&vars->img, x + 1, y + 2, 0xFFFFFF);
				my_mlx_pixel_put(&vars->img, x + 2, y, 0xFFFFFF);
				my_mlx_pixel_put(&vars->img, x + 2, y + 1, 0xFFFFFF);
				my_mlx_pixel_put(&vars->img, x + 2, y + 2, 0xFFFFFF);
			}
			y++;
		}
		//SET THE ZBUFFER FOR THE SPRITE CASTING
    	ZBuffer[x] = perpWallDist; //perpendicular distance is used
		x++;
	}
	//SPRITE CASTING
	//sort sprites from far to close
	int numSprites = vars->count_sprites;
	t_sprite sprite[numSprites];
	int k = 0;
	int j;
	int i = 0;

	while (vars->data.map[k])
	{
		j = 0;
		while (vars->data.map[k][j])
		{
			if (vars->data.map[k][j] == '2')
			{
				sprite[i].x = k + 0.5;
				sprite[i].y = j + 0.5;
				sprite[i].distance = ((posX - sprite[i].x) * (posX - sprite[i].x) + (posY - sprite[i].y) * (posY - sprite[i].y)); //sqrt not taken, unneeded
				i++;
			}
			j++;
		}
		k++;
	}
	// sortSprites(spriteOrder, spriteDistance, numSprites);

	//after sorting the sprites, do the projection and draw them
	for (int i = 0; i < numSprites; i++)
	{
		//translate sprite position to relative to camera
		double spriteX = sprite[i].x - posX;
		double spriteY = sprite[i].y - posY;
		double invDet = 1.0 / (vars->person.planeX * vars->person.dirY - vars->person.dirX * vars->person.planeY); //required for correct matrix multiplication

		double transformX = invDet * (vars->person.dirY * spriteX - vars->person.dirX * spriteY);
		double transformY = invDet * (-vars->person.planeY * spriteX + vars->person.planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

		int spriteScreenX = (int)((w / 2) * (1 + transformX / transformY));

		//calculate height of the sprite on screen
		int spriteHeight = fabs((double)(h / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + h / 2;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + h / 2;
		if (drawEndY >= h)
			drawEndY = h - 1;

		//calculate width of the sprite
		int spriteWidth = fabs((double)(h / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= w)
			drawEndX = w - 1;

		texHeight = vars->texture[4].height;
		texWidth = vars->texture[4].width;
		//loop through every vertical stripe of the sprite on screen
		for (int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if (transformY > 0 && stripe > 0 && stripe < w && transformY < ZBuffer[stripe])
				for (int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
				{
					int d = (y) * 256 - h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
					int texY = ((d * texHeight) / spriteHeight) / 256;
					int color = ft_get_color_2(&vars->texture[4], texX, texY); //get current color from the texture
					if ((color & 0x00FFFFFF) != 0)
						my_mlx_pixel_put(&vars->img, stripe, y, color); //paint pixel if it isn't black, black is the invisible color
					
				}
		}
	}
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img.img, 0, 0);
	mlx_destroy_image(vars->mlx_ptr,vars->img.img);
	return (0);
}