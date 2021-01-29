/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:54:32 by dwinky            #+#    #+#             */
/*   Updated: 2021/01/29 22:03:52 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"
#include <fcntl.h>
#include "mlx.h"

int		main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	int		fd;
	char	*line;
	void	*mlx_ptr;
	void	*win_ptr;

	if (argc != 2)
		return (-1);
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line))
	{
		ft_printf("%s\n", line);
		free(line);
	}
	ft_printf("%s\n", line);

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "planet");
	mlx_loop(mlx_ptr);
	return (0);
}
