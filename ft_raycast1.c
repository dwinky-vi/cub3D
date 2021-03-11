/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:29:38 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/12 01:43:35 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

int		ft_raycast(t_vars *vars)
{
	int		w;
	int		h;
	int		tex_w = 64;
	int		tex_h = 64;
	double	perpendiculars_array[vars->data.config.width];
	t_raycast ray;

	if (ft_init_img(vars->mlx_ptr, &vars->img, &vars->data.config))
		return (-1);
	w = vars->data.config.width;
	h = vars->data.config.height;
	ray.pos.x = vars->person.pos.x;
	ray.pos.y = vars->person.pos.y;
	make_step(vars);
	int x = 0;
	while (x < w)
	{
		// ray.camera_x [-1, 1] приведение значения ширины экрана к этим величинам 
		ray.camera_x = 2 * x / (double)w - 1;
		ray.dir.x = vars->person.dir.x + vars->person.plane.x * ray.camera_x;
		ray.dir.y = vars->person.dir.y + vars->person.plane.y * ray.camera_x;

		//which box of the map we're in
		ray.map.x = ray.pos.x;
		ray.map.y = ray.pos.y;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		ray.delta_dist_x = fabs(1 / ray.dir.x);
		ray.delta_dist_y = fabs(1 / ray.dir.y);
		double perpWallDist;

		int hit = FALSE; //was there a wall hit?
		if (ray.dir.x < 0)
		{
			ray.step.x = -1;
			sideDistX = (ray.pos.x - ray.map.x) * ray.delta_dist_x;
		}
		else
		{
			ray.step.x = 1;
			sideDistX = (ray.map.x + 1.0 - ray.pos.x) * ray.delta_dist_x;
		}
		if (ray.dir.y < 0)
		{
			ray.step.y = -1;
			sideDistY = (ray.pos.y - ray.map.y) * ray.delta_dist_y;
		}
		else
		{
			ray.step.y = 1;
			sideDistY = (ray.map.y + 1.0 - ray.pos.y) * ray.delta_dist_y;
		}
		while (hit == FALSE)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += ray.delta_dist_x;
				ray.map.x += ray.step.x;
				ray.side = 0;
			}
			else
			{
				sideDistY += ray.delta_dist_y;
				ray.map.y += ray.step.y;
				ray.side = 1; // вертикаль
			}
			if (vars->data.map[ray.map.x][ray.map.y] == '1')
				hit = TRUE;
		}
		if (ray.side == 0)  //вертикаль
			perpWallDist = (ray.map.x - ray.pos.x + (1 - ray.step.x) / 2) / ray.dir.x;
		else // горизанталь
			perpWallDist = (ray.map.y - ray.pos.y + (1 - ray.step.y) / 2) / ray.dir.y;
		ft_get_tex_width_height(vars, &tex_w, &tex_h, ray.side, ray.step.x, ray.step.y);
		int lineHeight = (int)(h / perpWallDist);
		ray.draw_start = -lineHeight / 2 + h / 2;
		if (ray.draw_start < 0)
			ray.draw_start = 0;
		ray.draw_end = lineHeight / 2 + h / 2;
		if (ray.draw_end >= h)
			ray.draw_end = h - 1;
		int texNum = vars->data.map[ray.map.x][ray.map.y] - 1; //1 subtracted from it so that texture 0 can be used!
		// это y-координата стены, если side == 1
		double wallX; 
		if (ray.side == 0)
			wallX = ray.pos.y + perpWallDist * ray.dir.y;
		else
			wallX = ray.pos.x + perpWallDist * ray.dir.x;
		wallX -= floor((wallX));
		ray.tex.x = wallX * tex_w;
		if (ray.side == 0 && ray.dir.x > 0)
			ray.tex.x = tex_w - ray.tex.x - 1;
		if (ray.side == 1 && ray.dir.y < 0)
			ray.tex.x = tex_w - ray.tex.x - 1;
		double step = 1.0 * tex_h / lineHeight;
		int y = 0;
		double texPos = (ray.draw_start - h / 2 + lineHeight / 2) * step;
		while (y < vars->data.config.height)
		{
			if (y < ray.draw_start) // потолок
				my_mlx_pixel_put(&vars->img, x, y, vars->data.config.c_int);
			else if (y > ray.draw_end) // пол
				my_mlx_pixel_put(&vars->img, x, y, vars->data.config.f_int);
			else // стена
			{
				ray.tex.y = (int)texPos & (tex_h - 1);
				texPos += step;
				int color = get_color_wall(vars, &ray);
				my_mlx_pixel_put(&vars->img, x, y, color);
			}
			y++;
		}
		perpendiculars_array[x] = perpWallDist;
		x++;
	}
	ft_spritecasting(vars, ray.pos.x, ray.pos.y, perpendiculars_array);
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img.img, 0, 0);
	mlx_destroy_image(vars->mlx_ptr, vars->img.img);
	return (0);
}

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
