/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spritecast1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:17:13 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/14 17:33:53 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

static void	ft_init_draw_point(t_spritecast *ray, t_config *config)
{
	int w;
	int h;

	w = config->width;
	h = config->height;
	ray->sprite_screen_x = w / 2 * (1 + ray->transform_x / ray->transform_y);
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
	int				x;
	int				y;
	int				d;
	unsigned int	color;
	t_point_i		tex;

	x = ray->draw_start_x - 1;
	while (++x < ray->draw_end_x)
	{
		tex.x = (x + ray->sprite_w / 2 - ray->sprite_screen_x) * \
					vars->texture[4].width / ray->sprite_w;
		if (ray->transform_y > 0 && 0 < x && x < vars->data.config.width &&
			ray->transform_y < pern_array[x])
		{
			y = ray->draw_start_y - 1;
			while (++y < ray->draw_end_y)
			{
				d = (y * 2 - vars->data.config.height + ray->sprite_h) * 128;
				tex.y = (d * vars->texture[4].height / ray->sprite_h) / 256;
				color = ft_mlx_get_color(&vars->texture[4], tex.x, tex.y);
				if ((color & (unsigned int)0x00FFFFFF) != 0)
					my_mlx_pixel_put(&vars->img, x, y, color);
			}
		}
	}
}

static void	ft_calculate_sprite_pos(t_spritecast *ray,
											t_sprite sprite, t_point_d *pos)
{
	ray->sprite_pos_x = sprite.x - pos->x;
	ray->sprite_pos_y = sprite.y - pos->y;
}

static void	ft_transforming(t_person *person, t_spritecast *ray)
{
	double			inv_det;

	inv_det = 1.0 / (person->plane.x * person->dir.y -
						person->dir.x * person->plane.y);
	ray->transform_x = inv_det * (person->dir.y * ray->sprite_pos_x -
									person->dir.x * ray->sprite_pos_y);
	ray->transform_y = inv_det * (-person->plane.y * ray->sprite_pos_x +
									person->plane.x * ray->sprite_pos_y);
}

void		ft_spritecast(t_vars *vars, t_point_d *pos, double *pern_array)
{
	int				k;
	t_sprite		sprite_array[vars->count_sprites];
	t_point_d		sprite_pos;
	t_spritecast	ray;

	ft_calculate_sprites(sprite_array, vars->data.map, pos);
	ft_quick_sort(sprite_array, 0, vars->count_sprites - 1);
	k = 0;
	while (k < vars->count_sprites)
	{
		ft_calculate_sprite_pos(&ray, sprite_array[k], pos);
		ft_transforming(&vars->person, &ray);
		ft_init_draw_point(&ray, &vars->data.config);
		ft_draw_vertic_stripe(vars, &ray, pern_array);
		k++;
	}
}
