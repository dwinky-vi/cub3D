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
// #include "minilibx_opengl_20191021/mlx.h"

/*
**	mlx_init() –– создаёт соединение между программным обеспеченнием и дисплеем
**   Никаких параметров не требуется, и он вернет идентификатор void *,
**   используемый для дальнейших вызовов библиотечных процедур.
**   Если соединение установить не получится, вернёт NULL.
**
*/

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
	// void		*mlx_ptr;
	// void		*win_ptr;
	int			fd;
	t_data		data;
	char		**map;

	fd = open(argv[1], O_RDONLY);
	data = ft_get_data(fd);

	ft_print_config(data.config);
	ft_print_map(data.map);

	ft_free_map(data.map);
	ft_free_config(&(data.config));
	close(fd);
	while (1);
/*
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "planet");
	mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0xFFFFFF);
	mlx_key_hook(win_ptr, deal_key, (void *)0);
	mlx_loop(mlx_ptr);
*/
	return (0);
}
