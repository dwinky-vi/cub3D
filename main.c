/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:54:32 by dwinky            #+#    #+#             */
/*   Updated: 2021/02/18 17:08:40 by dwinky           ###   ########.fr       */
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
	return (0);
}

void	ft_display_map(char **map, t_config config, t_vars vars)
{
	int 	k;
	int		j;
	int 	scale;
	t_point start;
	t_point	end;

	k = 0;
	scale = 18;
	while (map[k])
	{
		j = 0;
		while (map[k][j])
		{
			if (map[k][j] == '1')
			{
				start.x = k * scale;
				start.y = j * scale;
				end.x = (k + 1) * scale;
				end.y = (j + 1) * scale;
				while (start.x < end.x)
				{
					start.y = j * scale;
					while (start.y < end.y)
					{
						mlx_pixel_put(vars.mlx_ptr, vars.win_ptr, start.y, start.x, config.c_int);
						start.y++;
					}
					start.x++;
				}
			}
			j++;
		}
		k++;
	}
}

int		main(int argc, char **argv)
{
	(void)argc;
	void		*mlx_ptr;
	void		*win_ptr;
	int			fd;
	t_data		data;
	t_vars vars;
	char		*error;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_puterror("Error in fd"));
	data = ft_get_data(fd);
	if (data.error != NULL)
		return (ft_puterror(data.error));
	ft_print_config(data.config);
	ft_print_map(data.map);
	if ((error = ft_validator(&data)))
		return (ft_puterror(error));
	// ft_free_map(data.map);
	// ft_free_config(&(data.config));
	close(fd);
	
	vars.mlx_ptr = mlx_init();
	if (vars.mlx_ptr == NULL)
		return (ft_puterror("Error in mlx_init()"));
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, 1920, 1080, "planet");
	ft_display_map(data.map, data.config, vars);
	mlx_key_hook(vars.win_ptr, deal_key, &vars);
	mlx_loop(vars.mlx_ptr);
	return (0);
}
