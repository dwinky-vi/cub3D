/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_sprite.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:17:13 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/09 22:52:30 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

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

typedef struct	s_spritecast
{
	int		draw_start_y;
	int		draw_end_y;
	int		draw_start_x;
	int		draw_end_x;
	int		texture_h;
	int		texture_w;
	int		sprite_height;
	int		sprite_width;
	int		sprite_screen_x;
	double	transform_x;
	double	transform_y;
} 				t_spritecast;

void	ft_spritecasting(t_vars *vars, double pos_x, double pos_y, double *ZBuffer)
{
	int				w = vars->data.config.width;
	int				h = vars->data.config.height;
	int				i;
	int				numSprites = vars->count_sprites;
	t_sprite		sprite_array[numSprites];
	t_point_d		sprite_pos;
	t_spritecast	ray;

	ft_calculate_distance(sprite_array, vars->data.map, pos_x, pos_y);
	ft_quick_sort(sprite_array, 0, numSprites - 1);
	i = 0;
	while (i < numSprites)
	{
		//translate sprite position to relative to camera
		double spriteX = sprite_array[i].x - pos_x;
		double spriteY = sprite_array[i].y - pos_y;
		double invDet;
		invDet = 1.0 / (vars->person.planeX * vars->person.dirY - vars->person.dirX * vars->person.planeY); //required for correct matrix multiplication

		ray.transform_x = invDet * (vars->person.dirY * spriteX - vars->person.dirX * spriteY);
		double transformY = invDet * (-vars->person.planeY * spriteX + vars->person.planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

		int spriteScreenX = (int)((w / 2) * (1 + ray.transform_x / transformY));

		//calculate height of the sprite on screen
		ray.sprite_height = fabs((double)(h / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -ray.sprite_height / 2 + h / 2;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = ray.sprite_height / 2 + h / 2;
		if (drawEndY >= h)
			drawEndY = h - 1;

		//calculate width of the sprite
		ray.sprite_width = fabs((double)(h / (transformY)));
		int drawStartX = -ray.sprite_width / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		int drawEndX = ray.sprite_width / 2 + spriteScreenX;
		if (drawEndX >= w)
			drawEndX = w - 1;

		ray.texture_h = vars->texture[4].height;
		ray.texture_w = vars->texture[4].width;
		//loop through every vertical stripe of the sprite on screen
		for (int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (256 * (stripe - (-ray.sprite_width / 2 + spriteScreenX)) * ray.texture_w / ray.sprite_width) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if (transformY > 0 && stripe > 0 && stripe < w && transformY < ZBuffer[stripe])
				for (int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
				{
					int d = y * 256 - h * 128 + ray.sprite_height * 128; //256 and 128 factors to avoid floats
					int texY = ((d * ray.texture_h) / ray.sprite_height) / 256;
					int color = ft_mlx_get_color(&vars->texture[4], texX, texY); //get current color from the texture
					if ((color & 0x00FFFFFF) != 0)
						my_mlx_pixel_put(&vars->img, stripe, y, color); //paint pixel if it isn't black, black is the invisible color
				}
		}
		i++;
	}
}


// void	ft_draw_vertical_line_sprite(t_vars *vars, t_spritecast ray)
// {
// 	for (int stripe = ray.draw_start_x; stripe < ray.draw_end_x; stripe++)
// 		{
// 			int texX = (256 * (stripe - (-ray.sprite_width / 2 + ray.sprite_screen_x)) * vars->texture[4].width / ray.sprite_width) / 256;
// 			//the conditions in the if are:
// 			//1) it's in front of camera plane so you don't see things behind you
// 			//2) it's on the screen (left)
// 			//3) it's on the screen (right)
// 			//4) ZBuffer, with perpendicular distance
// 			if (ray.transform_y > 0 && stripe > 0 && stripe < vars->data.config.width && ray.transform_y < ZBuffer[stripe])
// 				for (int y = ray.draw_start_y; y < ray.draw_end_y; y++) //for every pixel of the current stripe
// 				{
// 					int d = y * 256 - vars->data.config.height * 128 + ray.sprite_height * 128; //256 and 128 factors to avoid floats
// 					int texY = ((d * vars->texture[4].height) / ray.sprite_height) / 256;
// 					int color = ft_mlx_get_color(&vars->texture[4], texX, texY); //get current color from the texture
// 					if ((color & 0x00FFFFFF) != 0)
// 						my_mlx_pixel_put(&vars->img, stripe, y, color); //paint pixel if it isn't black, black is the invisible color
// 				}
// 		}
// }