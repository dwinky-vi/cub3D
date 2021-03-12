/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spritecasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:17:13 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/12 17:23:43 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

double		power_2(double num)
{
	return (num * num);
}

static void	ft_calculate_distance(t_sprite *sprite, char **map,
								double pos_x, double pos_y)
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
				sprite[i].distance = power_2(pos_x - sprite[i].x) +
						power_2(pos_y - sprite[i].y);
				i++;
			}
			j++;
		}
		k++;
	}
}

static void	ft_init_draw_point(t_spritecast *ray, int h, int w)
{
	ray->sprite_screen_x = (int)((w / 2) *
							(1 + ray->transform_x / ray->transform_y));
	ray->sprite_h = fabs((double)(h / (ray->transform_y)));
	ray->draw_start_y = -ray->sprite_h / 2 + h / 2;
	if (ray->draw_start_y < 0)
		ray->draw_start_y = 0;
	ray->draw_end_y = ray->sprite_h / 2 + h / 2;
	if (ray->draw_end_y >= h)
		ray->draw_end_y = h - 1;
	ray->sprite_w = fabs((double)(h / (ray->transform_y)));
	ray->draw_start_x = -ray->sprite_w / 2 + ray->sprite_screen_x;
	if (ray->draw_start_x < 0)
		ray->draw_start_x = 0;
	ray->draw_end_x = ray->sprite_w / 2 + ray->sprite_screen_x;
	if (ray->draw_end_x >= w)
		ray->draw_end_x = w - 1;
}

/*
**stripe -- полоса
*/

static void	ft_draw_vertic_stripe(t_vars *vars, t_spritecast *ray,
									double *pern_array)
{
	int			x;
	int			y;
	int			d;
	int			color;
	t_point_i	tex;

	x = ray->draw_start_x;
	while (x < ray->draw_end_x)
	{
		tex.x = (256 * (x + ray->sprite_w / 2 - ray->sprite_screen_x) * vars->texture[4].width / ray->sprite_w) / 256;
		if (ray->transform_y > 0 && x > 0 && x < vars->data.config.width &&
			ray->transform_y < pern_array[x])
		{
			y = ray->draw_start_y;
			while (y < ray->draw_end_y)
			{
				d = y * 256 + (-vars->data.config.height + ray->sprite_h) * 128;
				tex.y = ((d * vars->texture[4].height) / ray->sprite_h) / 256;
				color = ft_mlx_get_color(&vars->texture[4], tex.x, tex.y);
				if ((ft_mlx_get_color(&vars->texture[4], tex.x, tex.y) & 0x00FFFFFF) != 0)
					my_mlx_pixel_put(&vars->img, x, y, color);
				y++;
			}
		}
		x++;
	}
}

void		ft_spritecasting(t_vars *vars, double pos_x,
								double pos_y, double *pern_array)
{
	int				i;
	int				num_sprites = vars->count_sprites;
	double			inv_det;
	t_sprite		sprite_array[num_sprites];
	t_point_d		sprite_pos;
	t_spritecast	ray;

	ft_calculate_distance(sprite_array, vars->data.map, pos_x, pos_y);
	ft_quick_sort(sprite_array, 0, num_sprites - 1);
	i = 0;
	while (i < num_sprites)
	{
		ray.sprite_pos_x = sprite_array[i].x - pos_x;
		ray.sprite_pos_y = sprite_array[i].y - pos_y;
		inv_det = 1.0 / (vars->person.plane.x * vars->person.dir.y - vars->person.dir.x * vars->person.plane.y);
		ray.transform_x = inv_det * (vars->person.dir.y * ray.sprite_pos_x - vars->person.dir.x * ray.sprite_pos_y);
		ray.transform_y = inv_det * (-vars->person.plane.y * ray.sprite_pos_x + vars->person.plane.x * ray.sprite_pos_y);
		ft_init_draw_point(&ray, vars->data.config.height, vars->data.config.width);
		ft_draw_vertic_stripe(vars, &ray, pern_array);
		i++;
	}
}
