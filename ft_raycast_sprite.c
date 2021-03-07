/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_sprite.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:17:13 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/07 17:48:09 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

void 	sortSprites(t_sprite *sprite, int count)
{
	int			k;
	int			j;
	t_sprite	buf;

	k = 0;
	while (k < count)
	{
		j = 0;
		while (j < count)
		{
			if (sprite[k].distance > sprite[j].distance)
			{
				buf = sprite[j];
				sprite[j] = sprite[k];
				sprite[k] = buf;
			}
			j++;
		}
		k++;
	}
}

void	ft_calculate_distance(t_sprite *sprite, char **map, double pos_x, double pos_y)
{
	int k;
	int j;
	int i;

	i = 0;
	k = 0;
	while (map[k])
	{
		j = 0;
		while (map[k][j])
		{
			if (map[k][j] == '2')
			{
				sprite[i].x = k + 0.5;
				sprite[i].y = j + 0.5;
				sprite[i].distance = ((pos_x - sprite[i].x) * (pos_x - sprite[i].x) + (pos_y - sprite[i].y) * (pos_y - sprite[i].y));
				i++;
			}
			j++;
		}
		k++;
	}
}

void	ft_spritecasting(t_vars *vars, double pos_x, double pos_y, double *ZBuffer)
{
	int			w = vars->data.config.width;
	int			h = vars->data.config.height;
	int			i;
	int			numSprites = vars->count_sprites;
	t_sprite	sprite[numSprites];

	ft_calculate_distance(sprite, vars->data.map, pos_x, pos_y);
	sortSprites(sprite, numSprites);
	i = 0;
	while (i < numSprites)
	{
		//translate sprite position to relative to camera
		double spriteX = sprite[i].x - pos_x;
		double spriteY = sprite[i].y - pos_y;
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

		int texHeight = vars->texture[4].height;
		int texWidth = vars->texture[4].width;
		//loop through every vertical stripe of the sprite on screen
		for (int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if (transformY > 0 && stripe > 0 && stripe < w && transformY < ZBuffer[stripe])
				for (int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
				{
					int d = y * 256 - h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
					int texY = ((d * texHeight) / spriteHeight) / 256;
					int color = ft_mlx_get_color(&vars->texture[4], texX, texY); //get current color from the texture
					if ((color & 0x00FFFFFF) != 0)
						my_mlx_pixel_put(&vars->img, stripe, y, color); //paint pixel if it isn't black, black is the invisible color
				}
		}
		i++;
	}
}
