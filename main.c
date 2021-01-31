/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:54:32 by dwinky            #+#    #+#             */
/*   Updated: 2021/01/31 14:53:02 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"
#include <fcntl.h>
#include "minilibx_opengl_20191021/mlx.h"

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
char	**ft_convert_lst_to_matrix(t_list *lst)
{
	int		k;
	int		j;
	char	**map;
	char	str;
	k = 0;
	// map = (char **)ft_calloc(ft_lstsize(list_map) + 1, sizeof(char *));
	map = (char **)malloc((ft_lstsize(lst) + 1) * sizeof(char *));
	if (map == NULL)
		return (-1);
	while (lst)
	{
		j = 0;
		str = (char *)(lst->content);
		lst = lst->next;
		while (str[j])
			j++;
		map[k] = ft_calloc(j + 1, 1);
		j = 0;
		while (str[j])
		{
			map[k][j] = str[j];
			j++;
		}
		k++;
	}
	return (map);
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
	t_list	*list_map;
	char	**map;

	if (argc != 2)
		return (-1);
	fd = open(argv[1], O_RDONLY);
	list = NULL;
	while (get_next_line(fd, &line))
	{
		if  (line[0] != '\0')
			ft_lstadd_back(&list, ft_lstnew(line));
		if (!(line[0] == 'R' || line[0] == 'S' || line[0] == 'F' || line[0] == 'G' ||
			(line[0] == 'N' && line[1] == 'O') ||
			(line[0] == 'S' && line[1] == 'O') ||
			(line[0] == 'W' && line[1] == 'E') ||
			(line[0] == 'E' && line[1] == 'A') ||
			line[0] == '\0'))
			break ;
	}
	// ft_lstprint_as_str(&list);
	list_map = NULL;
	while (get_next_line(fd, &line))
		if  (line[0] != '\0')
			ft_lstadd_back(&list_map, ft_lstnew(line));
	ft_lstadd_back(&list_map, ft_lstnew(line));
	// ft_lstprint_as_str(&list_map);

	map = ft_convert_lst_to_matrix(list_map);
	
	ft_printf("%s\n", map[0]);
	int		k;
	int		j;
	k = 0;
	while (map[k])
	{
		j = 0;
		while (map[k][j])
		{
			ft_putchar(map[k][j]);
			j++;
		}
		// ft_putstr(map[k]);
		ft_putchar('\n');
		k++;
	}
/*
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "planet");
	mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0xFFFFFF);
	mlx_key_hook(win_ptr, deal_key, (void *)0);
	mlx_loop(mlx_ptr);
*/
	return (0);
}
