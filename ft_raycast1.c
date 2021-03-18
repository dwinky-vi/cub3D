/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:29:38 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/18 07:42:07 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

/*
** Сначала рисуется потолок, потом стена, потом пол
** tex_pos берёт пиксель из текстуры и накладывает на стену
*/

static void	ft_draw_vertic_stripe(t_vars *vars, t_raycast *ray, int x)
{
	double	step;
	double	tex_pos;
	int		color;
	int		h;
	int		y;

	h = vars->data.config.height;
	step = (double)ray->tex_h / ray->draw_line_h;
	tex_pos = (ray->draw_start - h / 2 + ray->draw_line_h / 2) * step;
	y = 0;
	while (y < h)
	{
		if (y < ray->draw_start)
			my_mlx_pixel_put(&vars->img, x, y, vars->data.config.c_int);
		else if (y > ray->draw_end)
			my_mlx_pixel_put(&vars->img, x, y, vars->data.config.f_int);
		else
		{
			ray->tex.y = (int)tex_pos & (ray->tex_h - 1);
			tex_pos += step;
			color = get_color_wall(vars, ray);
			my_mlx_pixel_put(&vars->img, x, y, color);
		}
		y++;
	}
}

static void	ft_mega_helper(t_vars *vars, t_raycast *ray, int x)
{
	ft_calculate_value(ray, &vars->person, x, vars->data.config.width);
	ft_init_side_dist(ray);
	ft_calculate_dist_to_wall(ray, vars->data.map);
	ft_init_perp_dist_to_wall(ray);
	ft_get_tex_width_height(vars, ray);
	ft_calculate_line_h_to_draw(ray, vars->data.config.height);
	ft_calculate_value_of_wall_x(ray);
	ft_calculate_value_of_tex_x(ray);
	ft_draw_vertic_stripe(vars, ray, x);
}

int			ft_raycast(t_vars *vars)
{
	int			x;
	double		perpendiculars_array[vars->data.config.width];
	t_raycast	ray;

	if (ft_init_img(vars->mlx_ptr, &vars->img, &vars->data.config))
		return (-1);
	ray.pos.x = vars->person.pos.x;
	ray.pos.y = vars->person.pos.y;
	make_step(vars);
	x = 0;
	while (x < vars->data.config.width)
	{
		ft_mega_helper(vars, &ray, x);
		perpendiculars_array[x] = ray.perp_dist_to_wall;
		x++;
	}
	ft_spritecast(vars, &ray.pos, perpendiculars_array);
	if (vars->f_save == 0)
	{
		mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img.img, 0, 0);
		mlx_destroy_image(vars->mlx_ptr, vars->img.img);
	}
	return (0);
}
