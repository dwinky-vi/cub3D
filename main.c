/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:54:32 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/18 08:37:03 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"
#include <stdio.h>

#define ERROR00 "Error\n00 file is missing"
#define ERROR01 "Error\n01 Not valid file"
#define ERROR02 "Error\n02 Problem in mlx"
#define ERROR03 "Error\n03 Bad textures"

void		ft_make_screen(t_vars *vars, t_scrn *scrn, char *str)
{
	if (ft_strncmp(str, "--save", 6) == 0 && ft_strlen(str) == 6)
	{
		vars->f_save = TRUE;
		scrn->fd = open("screenshot.bmp", O_CREAT | O_RDWR | O_TRUNC, 0666);
		if (scrn->fd == -1)
		{
			ft_puterror("Error\nBad fn in screenshoot");
			exit(0);
		}
		vars->data.config.width = scrn->width;
		vars->data.config.height = scrn->height;
		ft_raycast(vars);
		ft_init_scrn(scrn);
		ft_write_bmp(scrn, vars->img.b_p_p);
		while (scrn->height > 0)
		{
			scrn->height--;
			write(scrn->fd, vars->img.addr + (scrn->height * vars->img.line_len),
			(scrn->width * (vars->img.b_p_p / 8)));
		}
		close(scrn->fd);
		exit(0);
	}
	ft_puterror("Error\nInvalid argv in screenshoot");
	exit(0);
}

int			main(int argc, char **argv)
{
	int		fd;
	t_vars	vars;
	t_scrn	scrn;

	if (argc == 1 || 3 < argc)
		return (ft_puterror(ERROR00));
	fd = ft_check_file_cub(argv[1]);
	if (fd == -1)
		return (ft_puterror(ERROR01));
	vars = ft_parse_data(fd);
	if (vars.data.error != NULL)
		return (ft_puterror(vars.data.error));
	scrn.width = vars.data.config.width;
	scrn.height = vars.data.config.height;
	printf("%d  %d\n", vars.data.config.width, vars.data.config.height);
	vars.data.error = ft_validator(&vars.data, vars.mlx_ptr);
	if (vars.data.error != NULL)
		return (ft_puterror(vars.data.error));
	close(fd);
	vars.mlx_ptr = mlx_init();
	if (ft_get_textures(vars.mlx_ptr, vars.texture, &vars.data.config))
		return (ft_puterror(ERROR03));
	if (argc == 3)
	{
		ft_make_screen(&vars, &scrn, argv[2]);
	}
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, vars.data.config.width, \
					vars.data.config.height, "CUB3D");
	if (vars.win_ptr == NULL)
		return (ft_puterror(ERROR02));
	ft_set_hooks(&vars);
	mlx_loop_hook(vars.mlx_ptr, ft_raycast, &vars);
	mlx_loop(vars.mlx_ptr);
	return (0);
}
