#include "ft_cub3d.h"
#define SCALE 18
#include <stdio.h>

/*
** a == 0
** s == 1
** d == 2
** w == 13
** esc = 53
*/

int		key_press_hook(int key, t_vars *vars)
{
	mlx_clear_window(vars->mlx_ptr, vars->win_ptr);
	if (key == 53)
		exit(0);
	if (key == 13)
		vars->k_13 = TRUE;
	if (key == 1)
		vars->k_1 = TRUE;
	if (key == 0)
		vars->k_0 = TRUE;
	if (key == 2)
		vars->k_2 = TRUE;
	if (vars->k_13)
	{
		if (vars->k_0)
			vars->person.dir += 0.1;
		else if (vars->k_2)
			vars->person.dir -= 0.1;
		vars->person.x += cos(vars->person.dir) * 0.1;
		vars->person.y += sin(vars->person.dir) * 0.1;
	}
	if (vars->k_1)
	{
		if (vars->k_0)
			vars->person.dir += 0.1;
		else if (vars->k_2)
			vars->person.dir -= 0.1;
		vars->person.x -= cos(vars->person.dir) * 0.1;
		vars->person.y -= sin(vars->person.dir) * 0.1;
	}
	if (vars->k_0)
	{
		vars->person.dir += 0.1;
	}
	if (vars->k_2)
	{
		vars->person.dir -= 0.1;
	}
	ft_display_map(vars);
	return (0);
}

int		key_release_hook(int key, t_vars *vars)
{
	if (key == 13)
	{
		vars->k_13 = FALSE;
		ft_putstr("13\n");
	}
	if (key == 1)
	{
		vars->k_1 = FALSE;
		ft_putstr("1\n");
	}
	if (key == 0)
	{
		vars->k_0 = FALSE;
		ft_putstr("0\n");
	}
	if (key == 2)
	{
		vars->k_2 = FALSE;
		ft_putstr("2\n");
	}
	return (0);
}

void	ft_draw_pixel(t_vars *vars, t_point start, t_point end, int color)
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

void	ft_cast_rays(t_vars *vars)
{
	// t_person	ray		= vars->person; // задаем координаты и направление луча равные координатам игрока
	float		start	= vars->person.dir - M_PI_4; // начало веера лучей
	float		end		= vars->person.dir + M_PI_4; // край веера лучей
	float		c;

	while (start < end)
	{
		c = 0;
		while (c < 20)
		{
			float cx = vars->person.x + c * cos(start);
			float cy = vars->person.y + c * sin(start);
			if (vars->data.map[(int)cx][(int)cy] == '1')
				break;
			my_mlx_pixel_put(&vars->img, cy * SCALE, cx * SCALE < 0 ? 0 : cx * SCALE, 0x990099);
			
			c += 0.05;
			// ray.x = vars->person.x; // каждый раз возвращаемся в точку начала
			// ray.y = vars->person.y;
			// while (vars->data.map[(int)(ray.x)][(int)(ray.y)] != '1')
			// {
			// 	ray.x += cos(ray.start);
			// 	ray.y += sin(ray.start);
			// 	my_mlx_pixel_put(&vars->img, ray.y * SCALE, ray.x * SCALE, 0x990099);
			// }
			// ray.start += M_PI_2 / 640;
		}
		start += M_PI_4 / 100;
	}
}

void	ft_draw_player(t_vars *vars, t_person *pl)
{
	t_person person = vars->person;
	t_point start;
	t_point	end;

	ft_cast_rays(vars);
	start.x = vars->person.x * SCALE;
	start.y = vars->person.y * SCALE;
	end.x = vars->person.x * SCALE + 2;
	end.y = vars->person.y * SCALE + 2;
	ft_draw_pixel(vars, start, end, vars->data.config.f_int);
}

void	ft_display_map(t_vars *vars)
{
	int 	k;
	int		j;
	t_point start;
	t_point	end;

    vars->img.img = mlx_new_image(vars->mlx_ptr, vars->data.config.r.size_x, vars->data.config.r.size_y);
    vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel, &vars->img.line_length, &vars->img.endian);
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
	ft_draw_player(vars, &vars->person);
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img.img, 0, 0);
}
