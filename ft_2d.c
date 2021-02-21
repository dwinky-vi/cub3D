#include "ft_cub3d.h"
#define SCALE 18
/*
** a == 0
** s == 1
** d == 2
** w == 13
** esc = 53
*/

int		deal_key(int key, t_vars *vars)
{
	mlx_clear_window(vars->mlx_ptr, vars->win_ptr);
	if (key == 53)
		exit(0);
	if (key == 13)
	{
		// if (vars->data.map[(int)vars->person.x - 1][(int)vars->person.y] != '1')
		// 	vars->person.x -= 1;
		vars->person.y += sin(vars->person.dir) * 1;
		vars->person.x += cos(vars->person.dir) * 1;
	}
	if (key == 1)
	{
		// if (vars->data.map[(int)vars->person.x + 1][(int)vars->person.y] != '1')
		// 	vars->person.x += 1;
		vars->person.y -= sin(vars->person.dir) * 1;
		vars->person.x -= cos(vars->person.dir) * 1;
	}
	if (key == 0)
	{
		// if (vars->data.map[(int)vars->person.x][(int)vars->person.y - 1] != '1')
		// 	vars->person.y -= 1;
		vars->person.dir -= 0.1;
	}
	if (key == 2)
	{
		// if (vars->data.map[(int)vars->person.x][(int)vars->person.y + 1] != '1')
		// 	vars->person.y += 1;
		vars->person.dir += 0.1;
	}
	ft_display_map(vars);
	return (0);
}

void	ft_draw_player(t_vars *vars, t_person *pl)
{
	t_person person = vars->person;

	// person.start = person.dir - M_PI_4;
	// person.end =  person.dir + M_PI_4;
//	while (person.start < person.end)
	// {
		//person.x = pl->x;
		//person.y = pl->y;
		while (vars->data.map[(int)(person.y / SCALE)][(int)(person.x / SCALE)] != '1')
		{
			person.x += cos(person.dir);
			person.y += sin(person.dir);
			my_mlx_pixel_put(&vars->img, person.x, person.y, 0x990099);
			// pixel_put(vars->win_ptr, person.x, person.y, 0x990099);

		}
		//plr.start += M_PI_2 7.640;
	// }
}

// void	ft_cast_ray(t_vars *vars)
// {
// 	t_person	ray = vars->person; // задаем координаты луча равные координатам игрока

// 	while (vars->data.map[(int)(ray.y)][(int)(ray.x)] != '1')
// 	{
// 		ray.x += cos(ray.dir);
// 		ray.y += sin(ray.dir);
// 		my_mlx_pixel_put(&vars->img, person.x, person.y, vars->data.config.f_int);
// 		// mlx_pixel_put(vars->mlx_ptr, vars->win_ptr, ray.x, ray.y, vars->data.config.f_int);
// 	}
// }

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
			end.x = (k + 1) * SCALE;
			end.y = (j + 1) * SCALE;
			if (vars->data.map[k][j] == '1')
			{
				while (start.x < end.x)
				{
					start.y = j * SCALE;
					while (start.y < end.y)
					{
						my_mlx_pixel_put(&vars->img, start.y, start.x, vars->data.config.c_int);
						start.y++;
					}
					start.x++;
				}
			}
			j++;
		}
		k++;
	}
	start.x = vars->person.x * SCALE;
	end.x = vars->person.x * SCALE + 10;
	end.y = vars->person.y * SCALE + 10;
	while (start.x < end.x)
	{
		start.y = vars->person.y * SCALE;
		while (start.y < end.y)
		{
			my_mlx_pixel_put(&vars->img, start.y, start.x, vars->data.config.f_int);
			start.y++;
		}
		start.x++;
	}
	ft_draw_player(vars, NULL);
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img.img, 0, 0);
}
