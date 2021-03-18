/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:54:32 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/18 09:11:41 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"
#include <stdio.h>

#define ERROR02 "Error\n02 Problem in mlx"
#define ERROR03 "Error\n03 Bad textures"

int			main(int argc, char **argv)
{
	int		fd;
	t_vars	vars;
	t_scrn	scrn;

	ft_check_arg(argc, argv[1], &fd);
	vars = ft_parse_data(fd);
	if (vars.data.error != NULL)
		return (ft_puterror(vars.data.error));
	vars.data.error = ft_validator(&vars, &vars.data, vars.mlx_ptr, &scrn);
	if (vars.data.error != NULL)
		return (ft_puterror(vars.data.error));
	close(fd);
	vars.mlx_ptr = mlx_init();
	if (ft_get_textures(vars.mlx_ptr, vars.texture, &vars.data.config))
		return (ft_puterror(ERROR03));
	if (argc == 3)
		ft_make_screen(&vars, &scrn, argv[2]);
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, vars.data.config.width, \
					vars.data.config.height, "CUB3D");
	if (vars.win_ptr == NULL)
		return (ft_puterror(ERROR02));
	ft_set_hooks(&vars);
	mlx_loop_hook(vars.mlx_ptr, ft_raycast, &vars);
	mlx_loop(vars.mlx_ptr);
	return (0);
}
