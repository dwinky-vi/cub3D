/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:54:32 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/07 17:50:29 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"
#include <stdio.h>

int			ft_puterror(char *str)
{
	ft_putendl_fd(str, 1);
	return (-1);
}

int			ft_get_textures(void *mlx, t_texture *texture, t_config *config)
{
	texture[0].img = mlx_xpm_file_to_image(mlx, config->no, &texture[0].width, &texture[0].height);
	texture[0].addr = mlx_get_data_addr(texture[0].img, &texture[0].bits_per_pixel, &texture[0].line_length, &texture[0].endian);
	if (texture[0].addr == NULL)
		return (1);
	texture[1].img = mlx_xpm_file_to_image(mlx, config->so, &texture[1].width, &texture[1].height);
	texture[1].addr = mlx_get_data_addr(texture[1].img, &texture[1].bits_per_pixel, &texture[1].line_length, &texture[1].endian);
	if (texture[1].addr == NULL)
		return (1);
	texture[2].img = mlx_xpm_file_to_image(mlx, config->we, &texture[2].width, &texture[2].height);
	texture[2].addr = mlx_get_data_addr(texture[2].img, &texture[2].bits_per_pixel, &texture[2].line_length, &texture[2].endian);
	if (texture[2].addr == NULL)
		return (1);
	texture[3].img = mlx_xpm_file_to_image(mlx, config->ea, &texture[3].width, &texture[3].height);
	texture[3].addr = mlx_get_data_addr(texture[3].img, &texture[3].bits_per_pixel, &texture[3].line_length, &texture[3].endian);
	if (texture[3].addr == NULL)
		return (1);
	texture[4].img = mlx_xpm_file_to_image(mlx, config->s, &texture[4].width, &texture[4].height);
	texture[4].addr = mlx_get_data_addr(texture[4].img, &texture[4].bits_per_pixel, &texture[4].line_length, &texture[4].endian);
	if (texture[4].addr == NULL)
		return (1);
	return (0);
}

void		ft_set_hooks(t_vars *vars)
{
	mlx_hook(vars->win_ptr, 2, 0, key_press_hook, vars);
	mlx_hook(vars->win_ptr, 3, 0, key_release_hook, vars);
	mlx_hook(vars->win_ptr, 17, 0, exit_hook, vars);
}

int			main(int argc, char **argv)
{
	int			fd;
	t_vars		vars;
	char		*error;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_puterror("Error in fd"));
	vars = ft_parse_data(fd);
	if (vars.data.error != NULL)
		return (ft_puterror(vars.data.error));
	if ((error = ft_validator(&vars.data, vars.mlx_ptr)))
		return (ft_puterror(error));
	close(fd);
	vars.mlx_ptr = mlx_init();
	if (vars.mlx_ptr == NULL)
		return (ft_puterror("Error in mlx_init()"));
	vars.win_ptr =
	mlx_new_window(vars.mlx_ptr, vars.data.config.width, vars.data.config.height, "CUB3D");
	if (ft_get_textures(vars.mlx_ptr, vars.texture, &vars.data.config))
		return (ft_puterror("Error\nBad textures"));
	ft_set_hooks(&vars);
	mlx_loop_hook(vars.mlx_ptr, ft_raycast, &vars);
	mlx_loop(vars.mlx_ptr);
	return (0);
}
