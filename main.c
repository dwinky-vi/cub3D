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

static int		ft_puterror(char *str)
{
	ft_putendl_fd(str, 1);
	return (-1);
}

void            my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int		main(int argc, char **argv)
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
	ft_display_map(&vars);
	
	// mlx_key_hook(vars.win_ptr, deal_key, &vars);
	mlx_hook(vars.win_ptr, 2, 1L << 0, deal_key, &vars);
	mlx_hook(vars.win_ptr, 2, 1L << 0, deal_key2, &vars);
	// mlx_hook(vars.win_ptr, 4, 1L<<8, closee, &vars);
    mlx_loop(vars.mlx_ptr);
	return (0);
}
