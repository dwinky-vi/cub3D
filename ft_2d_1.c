/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2d_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:29:31 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/07 14:06:53 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"
#include "head_2d.h"
#define SCALE 18

/*
** a = 0
** s = 1
** d = 2
** w = 13
** esc = 53
*/

void		ft_draw_pixel(t_vars *vars, t_point start, t_point end, int color)
{
	int tmp;

	tmp = start.y;
	while (start.x < end.x)
	{
		start.y = tmp;
		while (start.y < end.y)
		{
			my_mlx_pixel_put(&vars->img, start.y, start.x, color);
			start.y++;
		}
		start.x++;
	}
}

void		ft_draw_player(t_vars *vars)
{
	t_person	person;
	t_point		start;
	t_point		end;

	person = vars->person;
	ft_cast_rays(vars);
	start.x = vars->person.x * SCALE;
	start.y = vars->person.y * SCALE;
	end.x = vars->person.x * SCALE + 2;
	end.y = vars->person.y * SCALE + 2;
	ft_draw_pixel(vars, start, end, vars->data.config.f_int);
}

void		ft_display_map(t_vars *vars)
{
	int		k;
	int		j;
	t_point start;
	t_point	end;

	if (ft_init_img(vars->mlx_ptr, &vars->img, &vars->data.config))
		return ;
	k = 0;
	while (vars->data.map[k])
	{
		j = 0;
		while (vars->data.map[k][j])
		{
			start.x = k * SCALE;
			start.y = j * SCALE;
			end.x = (k + 1) * SCALE;
			end.y = (j + 1) * SCALE;
			if (vars->data.map[k][j] == '1')
				ft_draw_pixel(vars, start, end, vars->data.config.c_int);
			j++;
		}
		k++;
	}
	ft_draw_player(vars);
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img.img, 0, 0);
}

void		ft_cast_rays(t_vars *vars)
{
	float	start;
	float	end;
	float	c;
	float	cx;
	float	cx;

	start = vars->person.dir - M_PI_4;
	end = vars->person.dir + M_PI_4;
	while (start < end)
	{
		c = 0;
		while (c < 20)
		{
			cx = vars->person.x + c * cos(start);
			cy = vars->person.y + c * sin(start);
			if (vars->data.map[(int)cx][(int)cy] == '1')
				break ;
			my_mlx_pixel_put(&vars->img, cy * SCALE, cx < 0 ? 0 : cx * SCALE,
								0x990099);
			c += 0.05;
		}
		start += M_PI_4 / 100;
	}
}

int			ft_init_img(void *mlx_ptr, t_img *img, t_config *config)
{
	img->img = mlx_new_image(mlx_ptr, config->width, config->height);
	if (img->img == NULL)
		return (1);
	img->addr = mlx_get_data_addr(img->img, img->bits_per_pixel,
									img->line_length, img->endian);
}
