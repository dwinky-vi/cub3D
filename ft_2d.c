#include "ft_cub3d.h"

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
		if (vars->data.map[vars->person.x - 1][vars->person.y] != '1')
			vars->person.x -= 1;
	if (key == 1)
		if (vars->data.map[vars->person.x + 1][vars->person.y] != '1')
			vars->person.x += 1;
	if (key == 0)
		if (vars->data.map[vars->person.x][vars->person.y - 1] != '1')
			vars->person.y -= 1;
	if (key == 2)
		if (vars->data.map[vars->person.x][vars->person.y + 1] != '1')
			vars->person.y += 1;
	ft_display_map(vars);
	return (0);
}

void	ft_display_map(t_vars *vars)
{
	int 	k;
	int		j;
	int 	scale;
	t_point start;
	t_point	end;

    vars->img.img = mlx_new_image(vars->mlx_ptr, vars->data.config.r.size_x, vars->data.config.r.size_y);
    vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel, &vars->img.line_length, &vars->img.endian);
	k = 0;
	scale = 20;
	while (vars->data.map[k])
	{
		j = 0;
		while (vars->data.map[k][j])
		{
			start.x = k * scale;
			end.x = (k + 1) * scale;
			end.y = (j + 1) * scale;
			if (vars->data.map[k][j] == '1')
			{
				while (start.x < end.x)
				{
					start.y = j * scale;
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
	start.x = vars->person.x * scale;
	end.x = (vars->person.x + 1) * scale;
	end.y = (vars->person.y + 1) * scale;
	while (start.x < end.x)
	{
		start.y = vars->person.y * scale;
		while (start.y < end.y)
		{
			my_mlx_pixel_put(&vars->img, start.y, start.x, vars->data.config.f_int);
			start.y++;
		}
		start.x++;
	}
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img.img, 0, 0);
}
