/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 22:41:24 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/12 19:44:36 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

/*
** camera_x [-1, 1] приведение значения ширины экрана к этим величинам
*/

void		ft_calculate_value(t_raycast *ray, t_person *person, int x, int w)
{
	ray->camera_x = 2 * x / (double)w - 1;
	ray->dir.x = person->dir.x + person->plane.x * ray->camera_x;
	ray->dir.y = person->dir.y + person->plane.y * ray->camera_x;
	ray->map.x = ray->pos.x;
	ray->map.y = ray->pos.y;
	ray->delta_dist.x = fabs(1 / ray->dir.x);
	ray->delta_dist.y = fabs(1 / ray->dir.y);
}

/*
** calculate step and initial side_dist
*/

void		ft_init_side_dist(t_raycast *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (ray->pos.x - ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.x + 1.0 - ray->pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (ray->pos.y - ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - ray->pos.y) * ray->delta_dist.y;
	}
}

void		ft_calculate_dist_to_wall(t_raycast *ray, char **map)
{
	int hit;

	hit = FALSE;
	while (hit == FALSE)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (map[ray->map.x][ray->map.y] == '1')
			hit = TRUE;
	}
}

/*
** side == 0 –– вертикаль
** side == 1 –– горизанталь
*/

void		ft_init_perp_dist_to_wall(t_raycast *ray)
{
	if (ray->side == 0)
		ray->perp_dist_to_wall =
				(ray->map.x - ray->pos.x + (1 - ray->step.x) / 2) / ray->dir.x;
	else
		ray->perp_dist_to_wall =
				(ray->map.y - ray->pos.y + (1 - ray->step.y) / 2) / ray->dir.y;
}
