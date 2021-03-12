/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 19:43:27 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/12 19:44:42 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

void		ft_get_tex_width_height(t_vars *vars, t_raycast *ray)
{
	if (ray->side == 0 && ray->step.x == -1)
	{
		ray->tex_h = vars->texture[0].height;
		ray->tex_w = vars->texture[0].width;
	}
	else if (ray->side == 0 && ray->step.x == 1)
	{
		ray->tex_h = vars->texture[1].height;
		ray->tex_w = vars->texture[1].width;
	}
	else if (ray->step.y == -1)
	{
		ray->tex_h = vars->texture[2].height;
		ray->tex_w = vars->texture[2].width;
	}
	else if (ray->step.y == 1)
	{
		ray->tex_h = vars->texture[3].height;
		ray->tex_w = vars->texture[3].width;
	}
}

/*
** Вычисляет длину линии draw_line_h, которая должна быть нарисована на экране.
** Это величина, обратная perp_dist_to_wall, а затем умноженная на h.
** draw_line_h представляет собой высоту верт. линии, которую нужно нарисовать.
** вычисляются начальная и конечная позиции,
** где мы должны действительно рисовать.
*/

void		ft_calculate_line_h_to_draw(t_raycast *ray, int h)
{
	ray->draw_line_h = h / ray->perp_dist_to_wall;
	ray->draw_start = -ray->draw_line_h / 2 + h / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->draw_line_h / 2 + h / 2;
	if (ray->draw_end >= h)
		ray->draw_end = h - 1;
}

/*
**	Значение wall_x представляет собой точное значение точки удара о стену,
** а не только целые координаты стены. Это необходимо, чтобы знать,
** какую x-координату текстуры мы должны использовать.
** Это вычисляется, сначала вычисляя точную координату x или y в мире,
** а затем вычитая из нее целое значение стены.
** Обратите внимание, что даже если он называется wallX,
** на самом деле это y-координата стены, если side == 1,
** но это всегда x-координата текстуры.
*/

void		ft_calculate_value_of_wall_x(t_raycast *ray)
{
	if (ray->side == 0)
		ray->wall_x = ray->pos.y + ray->perp_dist_to_wall * ray->dir.y;
	else
		ray->wall_x = ray->pos.x + ray->perp_dist_to_wall * ray->dir.x;
	ray->wall_x -= floor(ray->wall_x);
}

void		ft_calculate_value_of_tex_x(t_raycast *ray)
{
	ray->tex.x = ray->wall_x * ray->tex_w;
	if (ray->side == 0 && ray->dir.x > 0)
		ray->tex.x = ray->tex_w - ray->tex.x - 1;
	else if (ray->side == 1 && ray->dir.y < 0)
		ray->tex.x = ray->tex_w - ray->tex.x - 1;
}

int			get_color_wall(t_vars *vars, t_raycast *ray)
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
