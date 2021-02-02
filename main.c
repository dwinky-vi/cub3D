/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:54:32 by dwinky            #+#    #+#             */
/*   Updated: 2021/01/31 21:27:09 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"
#include <fcntl.h>
#include "minilibx_opengl_20191021/mlx.h"

int		deal_key(int key, void *param)
{
	ft_putnbr(key);
	ft_putchar(' ');
	param = NULL;
	// mlx_pixel_put(mlx_ptr, win_ptr, );
	return (0);
}

int		main(int argc, char **argv)
{
	(void)argc;
	void		*mlx_ptr;
	void		*win_ptr;
	int			fd;
	t_data		data;
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
	ft_free_map(data.map);
	ft_free_config(&(data.config));
	close(fd);
	while (1);

/*
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1920, 1080, "planet");
	mlx_pixel_put(mlx_ptr, win_ptr, 1150, 250, 0xFFFFFF);
	mlx_key_hook(win_ptr, deal_key, (void *)0);
	mlx_loop(mlx_ptr);
*/
	return (0);
}
