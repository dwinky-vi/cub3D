/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:54:32 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/03 22:19:26 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"
#include <stdio.h>

static int	mouse_press_hook(int key, void *vars)
{
	ft_putchar(key);
	ft_putchar('1');
	return (0);
}

static int	motion_hook(int key, void *vars)
{
	ft_putnbr(key);
	ft_putchar('2');
	return (0);
}

static int	expose_hook(int key, void *vars)
{
	ft_putnbr(key);
	ft_putchar('\n');
	return (0);
}

static int	ft_puterror(char *str)
{
	ft_putendl_fd(str, 1);
	return (-1);
}

void		my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int			main(int argc, char **argv)
{
	(void)argc;
	int			fd;
	t_vars 		vars;
	char		*error;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_puterror("Error in fd"));
	vars = ft_parse_data(fd);
	if (vars.data.error != NULL)
		return (ft_puterror(vars.data.error));
	// ft_print_config(vars.data.config);
	// ft_print_map(vars.data.map);
	if ((error = ft_validator(&vars.data)))
		return (ft_puterror(error));
	close(fd);
	vars.mlx_ptr = mlx_init();
	if (vars.mlx_ptr == NULL)
		return (ft_puterror("Error in mlx_init()"));
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, vars.data.config.r.size_x, vars.data.config.r.size_y, "planet");
/**********************************************/
  	// double dirX = -1, dirY = 0; //initial direction vector
// обнулить key_code
	vars.person.moveSpeed = 0.05; // скорость ходьбы
	vars.person.rotSpeed = 0.03; // скорость поворотов

/**********************************************/
	mlx_hook(vars.win_ptr, 2, 0, key_press_hook, &vars);
	mlx_hook(vars.win_ptr, 3, 0, key_release_hook, &vars);
	mlx_hook(vars.win_ptr, 17, 0, exit_hook, &vars);
	mlx_loop_hook(vars.mlx_ptr, ft_raycast, &vars);
    mlx_loop(vars.mlx_ptr);
	return (0);
}
