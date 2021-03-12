/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 22:41:24 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/12 04:21:01 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

int		get_color_wall(t_vars *vars, t_raycast *ray)
{
	int color;

	if (ray->side == 0 && ray->step.x == -1)
		color = ft_mlx_get_color(&vars->texture[0], ray->tex.x, ray->tex.y);
	else if (ray->side == 0 && ray->step.x == 1)
		color = ft_mlx_get_color(&vars->texture[1], ray->tex.x, ray->tex.y);
	else if (ray->step.y == -1)
		color = ft_mlx_get_color(&vars->texture[2], ray->tex.x, ray->tex.y);
	else if (ray->step.y == 1)
		color = ft_mlx_get_color(&vars->texture[3], ray->tex.x, ray->tex.y);
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

void	ft_init_side_dist(t_raycast *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (ray->pos.x - ray->map.x) * ray->delta_dist_x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.x + 1.0 - ray->pos.x) * ray->delta_dist_x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (ray->pos.y - ray->map.y) * ray->delta_dist_y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - ray->pos.y) * ray->delta_dist_y;
	}
}

void	ft_calculate_dist_to_wall(t_raycast *ray, char **map)
{
	int hit;

	hit = FALSE;
	while (hit == FALSE)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist_x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist_y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (map[ray->map.x][ray->map.y] == '1')
			hit = TRUE;
	}
}
