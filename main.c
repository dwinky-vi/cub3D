/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:54:32 by dwinky            #+#    #+#             */
/*   Updated: 2021/01/30 20:45:45 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"
#include <fcntl.h>
#include "mlx.h"

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
	(void)argc;
	(void)argv;
	int		fd;
	char	*line;
	void	*mlx_ptr;
	void	*win_ptr;
	t_list	*list;

	if (argc != 2)
		return (-1);
	fd = open(argv[1], O_RDONLY);
	list = NULL;
	while (get_next_line(fd, &line))
		ft_lstadd_back(&list, ft_lstnew(line));
	while (list)
	{
		ft_printf("%s\n", (char *)(list->content));
		list = list->next;
	}
	// ft_printf("%s\n", line);
/*
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "planet");
	mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0xFFFFFF);
	mlx_key_hook(win_ptr, deal_key, (void *)0);
	mlx_loop(mlx_ptr);
*/
	return (0);
}
