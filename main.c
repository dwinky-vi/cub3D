/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:54:32 by dwinky            #+#    #+#             */
/*   Updated: 2021/02/18 21:26:28 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"
// #include "minilibx_opengl_20191021/mlx.h"

/*
** a == 0
** s == 1
** d == 2
** w == 13
** esc = 53
*/

int		deal_key(int key, t_vars *vars)
{
	if (key == 53)
	{
		mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
		exit(0);
	}
	if (key == 13)
	{
		vars->person.x -= 1;
		ft_display_map(*vars);
	}
	if (key == 1)
	{
		vars->person.x += 1;
		ft_display_map(*vars);
	}
	if (key == 0)
	{
		vars->person.y -= 1;
		ft_display_map(*vars);
	}
	if (key == 2)
	{
		vars->person.y += 1;
		ft_display_map(*vars);
	}
	return (0);
}


void            my_mlx_pixel_put(t_data2 *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}


void	ft_display_map(t_vars vars)
{
	int 	k;
	int		j;
	int 	scale;
	t_point start;
	t_point	end;

    vars.img.img = mlx_new_image(vars.mlx_ptr, 1920, 1080);
    vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);
	k = 0;
	scale = 18;
	while (vars.data.map[k])
	{
		j = 0;
		while (vars.data.map[k][j])
		{
			start.x = k * scale;
			start.y = j * scale;
			end.x = (k + 1) * scale;
			end.y = (j + 1) * scale;
			if (vars.data.map[k][j] == '1')
			{
				while (start.x < end.x)
				{
					start.y = j * scale;
					while (start.y < end.y)
					{
						my_mlx_pixel_put(&vars.img, start.y, start.x, vars.data.config.c_int);
						start.y++;
					}
					start.x++;
				}
			}
			j++;
		}
		k++;
	}
	start.x = vars.person.x * scale;
	end.x = (vars.person.x + 1) * scale;
	end.y = (vars.person.y + 1) * scale;
	while (start.x < end.x)
	{
		start.y = vars.person.y * scale;
		while (start.y < end.y)
		{
			my_mlx_pixel_put(&vars.img, start.y, start.x, vars.data.config.f_int);
			start.y++;
		}
		start.x++;
	}
	mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.img.img, 0, 0);
}

int		main(int argc, char **argv)
{
	(void)argc;
	void		*mlx_ptr;
	void		*win_ptr;
	int			fd;
	// t_data		data;
	t_vars 		vars;
	char		*error;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_puterror("Error in fd"));
	vars.data = ft_get_data(fd);
	if (vars.data.error != NULL)
		return (ft_puterror(vars.data.error));
	ft_print_config(vars.data.config);
	ft_print_map(vars.data.map);
	if ((error = ft_validator(&vars.data)))
		return (ft_puterror(error));
	// ft_free_map(data.map);
	// ft_free_config(&(data.config));
	close(fd);
	
	vars.mlx_ptr = mlx_init();
	if (vars.mlx_ptr == NULL)
		return (ft_puterror("Error in mlx_init()"));
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, 1920, 1080, "planet");

	
	int k = 0;
	while (vars.data.map[k])
	{
		int j = 0;
		while (vars.data.map[k][j])
		{
			if (vars.data.map[k][j] == 'N' || vars.data.map[k][j] == 'S' || vars.data.map[k][j] == 'E' || vars.data.map[k][j] == 'W')
			{
				vars.person.x = k;
				vars.person.y = j;
			}
			j++;
		}
		k++;
	}
	
	ft_display_map(vars);
	
	mlx_key_hook(vars.win_ptr, deal_key, &vars);
    mlx_loop(vars.mlx_ptr);
	return (0);
}
