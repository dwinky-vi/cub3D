/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:54:32 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/04 15:55:20 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"
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

int			ft_puterror(char *str)
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

int			ft_get_textures(t_vars *vars)
{
	vars->texture[0].img = mlx_xpm_file_to_image(vars->mlx_ptr, vars->data.config.no, &vars->texture[0].width, &vars->texture[0].height);
	if (vars->texture[0].img == NULL)
		return (-1);
	vars->texture[1].addr = mlx_get_data_addr(vars->texture[1].img, &vars->texture[1].bits_per_pixel, &vars->texture[1].line_length, &vars->texture[1].endian);
	
	vars->texture[1].img = mlx_xpm_file_to_image(vars->mlx_ptr, vars->data.config.so, &vars->texture[1].width, &vars->texture[1].height);
	if (vars->texture[1].img == NULL)
		return (-1);
	vars->texture[1].addr = mlx_get_data_addr(vars->texture[1].img, &vars->texture[1].bits_per_pixel, &vars->texture[1].line_length, &vars->texture[1].endian);
	
	vars->texture[1].img = mlx_xpm_file_to_image(vars->mlx_ptr, vars->data.config.we, &vars->texture[1].width, &vars->texture[1].height);
	if (vars->texture[1].img == NULL)
		return (-1);
	vars->texture[1].addr = mlx_get_data_addr(vars->texture[1].img, &vars->texture[1].bits_per_pixel, &vars->texture[1].line_length, &vars->texture[1].endian);

	vars->texture[1].img = mlx_xpm_file_to_image(vars->mlx_ptr, vars->data.config.no, &vars->texture[1].width, &vars->texture[1].height);
	if (vars->texture[1].img == NULL)
		return (-1);
	vars->texture[1].addr = mlx_get_data_addr(vars->texture[1].img, &vars->texture[1].bits_per_pixel, &vars->texture[1].line_length, &vars->texture[1].endian);

	vars->texture[1].img = mlx_xpm_file_to_image(vars->mlx_ptr, vars->data.config.s, &vars->texture[1].width, &vars->texture[1].height);
	if (vars->texture[1].img == NULL)
		return (-1);
	vars->texture[1].addr = mlx_get_data_addr(vars->texture[1].img, &vars->texture[1].bits_per_pixel, &vars->texture[1].line_length, &vars->texture[1].endian);
	
	return (0);
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
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, vars.data.config.r.width, vars.data.config.r.height, "planet");
/**********************************************/
  	// double dirX = -1, dirY = 0; //initial direction vector
// обнулить key_code
	vars.person.moveSpeed = 0.05; // скорость ходьбы
	vars.person.rotSpeed = 0.03; // скорость поворотов

/**********************************************/
	ft_get_textures(&vars);
	mlx_hook(vars.win_ptr, 2, 0, key_press_hook, &vars);
	mlx_hook(vars.win_ptr, 3, 0, key_release_hook, &vars);
	mlx_hook(vars.win_ptr, 17, 0, exit_hook, &vars);
	mlx_loop_hook(vars.mlx_ptr, ft_raycast, &vars);
    mlx_loop(vars.mlx_ptr);
	return (0);
}
