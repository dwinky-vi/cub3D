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

t_config	ft_get_config(int fd)
{
	t_config	config;
	char		*line;
	char		*tmp;
	int			k;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		tmp = line;
		line = ft_strtrim(line, " ");
		free(tmp);
		if (line[0] == 'R')
			config.r = ft_strtrim(line + 1, " ");
		else if (line[0] == 'N' && line[1] == 'O')
			config.no = ft_strtrim(line + 2, " ");
		else if (line[0] == 'S' && line[1] == 'O')
			config.so = ft_strtrim(line + 2, " ");
		else if (line[0] == 'W' && line[1] == 'E')
			config.we = ft_strtrim(line + 2, " ");
		else if (line[0] == 'E' && line[1] == 'A')
			config.ea = ft_strtrim(line + 2, " ");
		else if (line[0] == 'S')
			config.s = ft_strtrim(line + 1, " ");
		else if (line[0] == 'F')
			config.f = ft_strtrim(line + 1, " ");
		else if (line[0] == 'C')
			config.c = ft_strtrim(line + 1, " ");
		else if (line[0] == '\0')
		{
			free(line);
			continue;
		}
		else
			return (config);
		ft_putendl_fd(line, 1);
		free(line);
	}
	free(line);
	return (config);
}

void		ft_make_list_map(int fd, t_list **list_map)
{
	char	*line;

	*list_map = NULL;
	while (get_next_line(fd, &line))
	{
		if (line[0] == 'R' || line[0] == 'S' || line[0] == 'F' || line[0] == 'G' ||
			(line[0] == 'N' && line[1] == 'O') ||
			(line[0] == 'S' && line[1] == 'O') ||
			(line[0] == 'W' && line[1] == 'E') ||
			(line[0] == 'E' && line[1] == 'A') ||
			line[0] == '\0')
			continue ;
		if  (line[0] != '\0')
			ft_lstadd_back(list_map, ft_lstnew(line));
	}
	ft_lstadd_back(list_map, ft_lstnew(line));
}

char	**ft_convert_lst_to_matrix(t_list **lst)
{
	int		k;
	int		j;
	char	**map;
	char	*line;
	t_list	*cur_lst;

	if (!(map = (char **)ft_calloc(ft_lstsize(*lst) + 1, sizeof(char *))))
		return (NULL);
	k = 0;
	while (*lst)
	{
		line = (char *)((*lst)->content);
		cur_lst = *lst;
		*lst = (*lst)->next;
		map[k] = ft_calloc(ft_strlen(line) + 1, 1);
		if (map[k] == NULL)
		{
			while (k-- > 0)
				free(map[k]);
			free(map);
			return (NULL);
		}
		j = -1;
		while (line[++j])
			map[k][j] = line[j];
		k++;
		ft_lstdelone(cur_lst, free);
	}
	return (map);
}

char	**ft_get_map(int fd)
{
	char	**map;
	t_list	*list_map;

	ft_make_list_map(fd, &list_map);
	map = ft_convert_lst_to_matrix(&list_map);
	return (map);
}

int		main(int argc, char **argv)
{
	// void		*mlx_ptr;
	// void		*win_ptr;
	int			fd;
	t_config	config;
	char		**map;

	fd = open(argv[1], O_RDONLY);
	config = ft_get_config(fd);
	if (!(map = ft_get_map(fd)))
		return (-1);

	ft_print_map(map);
	ft_free_map(map);
	ft_free_config(&config);
	// while (1);
/*
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "planet");
	mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0xFFFFFF);
	mlx_key_hook(win_ptr, deal_key, (void *)0);
	mlx_loop(mlx_ptr);
*/
	return (0);
}
