/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:29:38 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/12 18:00:00 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"
#include <time.h>
#include <stdio.h>

static void	ft_draw_vertic_stripe(t_vars *vars, t_raycast *ray, int x, int h)
{
	double step;
	double texPos = (ray->draw_start - h / 2 + ray->draw_line_h / 2) * step;
	int y;
	int	color;
	// int h;
	step = 1.0 * ray->tex_h / ray->draw_line_h;
	// h = vars->data.config.height;
	y = 0;
	while (y < h)
	{
		if (y < ray->draw_start) // потолок
			my_mlx_pixel_put(&vars->img, x, y, vars->data.config.c_int);
		else if (y > ray->draw_end) // пол
			my_mlx_pixel_put(&vars->img, x, y, vars->data.config.f_int);
		else // стена
		{
			ray->tex.y = (int)texPos & (ray->tex_h - 1);
			texPos += step;
			color = get_color_wall(vars, ray);
			my_mlx_pixel_put(&vars->img, x, y, color);
		}
		y++;
	}
}

int		ft_raycast(t_vars *vars)
{
	int			w;
	int			h;
	int			x;
	double		perpendiculars_array[vars->data.config.width];
	t_raycast	ray;
	int			start_time;
	int			end_time;

	if (ft_init_img(vars->mlx_ptr, &vars->img, &vars->data.config))
		return (-1);
	w = vars->data.config.width;
	h = vars->data.config.height;
	ray.pos.x = vars->person.pos.x;
	ray.pos.y = vars->person.pos.y;
	make_step(vars);
	start_time = clock();
	x = 0;
	while (x < w)
	{
	// ray.camera_x [-1, 1] приведение значения ширины экрана к этим величинам
		ray.camera_x = 2 * x / (double)w - 1;
		ray.dir.x = vars->person.dir.x + vars->person.plane.x * ray.camera_x;
		ray.dir.y = vars->person.dir.y + vars->person.plane.y * ray.camera_x;
		//which box of the map we're in
		ray.map.x = ray.pos.x;
		ray.map.y = ray.pos.y;

		ray.delta_dist.x = fabs(1 / ray.dir.x);
		ray.delta_dist.y = fabs(1 / ray.dir.y);
		ft_init_side_dist(&ray);
		ft_calculate_dist_to_wall(&ray, vars->data.map);
		ft_init_perp_dist_to_wall(&ray);
		ft_get_tex_width_height(vars, &ray.tex_w, &ray.tex_h, ray.side, ray.step.x, ray.step.y);
		ft_calculate_line_h_to_draw(&ray, h);
		ft_calculate_value_of_wall_x(&ray);
		ft_calculate_value_of_tex_x(&ray);
		ft_draw_vertic_stripe(vars, &ray, x, h);
		
		
		perpendiculars_array[x] = ray.perp_dist_to_wall;
		x++;
	}
	ft_spritecasting(vars, ray.pos.x, ray.pos.y, perpendiculars_array);
	end_time = clock();
	// printf("%.2f\n", (end_time - start_time) / 10000.); //FPS counter
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img.img, 0, 0);
	mlx_destroy_image(vars->mlx_ptr, vars->img.img);
	return (0);
}

/*
** side == 0 –– вертикаль
** side == 1 –– горизанталь
*/

void	ft_init_perp_dist_to_wall(t_raycast *ray)
{
	if (ray->side == 0)
		ray->perp_dist_to_wall = (ray->map.x - ray->pos.x + (1 - ray->step.x) / 2) / ray->dir.x;
	else
		ray->perp_dist_to_wall = (ray->map.y - ray->pos.y + (1 - ray->step.y) / 2) / ray->dir.y;
}

/*
** Вычисляет длину линии draw_line_h, которая должна быть нарисована на экране.
** Это величина, обратная perp_dist_to_wall, а затем умноженная на h.
** draw_line_h представляет собой высоту верт. линии, которую нужно нарисовать.
** вычисляются начальная и конечная позиции,
** где мы должны действительно рисовать.
*/

void	ft_calculate_line_h_to_draw(t_raycast *ray, int h)
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

void	ft_calculate_value_of_wall_x(t_raycast *ray)
{
	if (ray->side == 0)
		ray->wall_x = ray->pos.y + ray->perp_dist_to_wall * ray->dir.y;
	else
		ray->wall_x = ray->pos.x + ray->perp_dist_to_wall * ray->dir.x;
	ray->wall_x -= floor(ray->wall_x);
}
void	ft_calculate_value_of_tex_x(t_raycast *ray)
{
	ray->tex.x = ray->wall_x * ray->tex_w;
	if (ray->side == 0 && ray->dir.x > 0)
		ray->tex.x = ray->tex_w - ray->tex.x - 1;
	else if (ray->side == 1 && ray->dir.y < 0)
		ray->tex.x = ray->tex_w - ray->tex.x - 1;
}