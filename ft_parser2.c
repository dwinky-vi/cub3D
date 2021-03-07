/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:29:42 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/07 14:13:44 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"
#include "head_parser.h"

static int	ft_get_width(char *str)
{
	char	*tmp;
	int		width;

	tmp = str;
	width = ft_atoi(str);
	while (ft_isdigit(*str))
		str++;
	free(tmp);
	return (width);
}

static int	ft_get_height(char *str)
{
	char	*tmp;
	int		height;

	tmp = str;
	while (ft_isdigit(*str))
		str++;
	while (!ft_isdigit(*str))
		str++;
	height = ft_atoi(str);
	free(tmp);
	return (height);
}

void		ft_set_config(t_config *config, char *line)
{
	if (line[0] == 'R' && config->width != 0)
	{
		config->width = 0;
		return ;
	}
	else if (line[0] == 'N' && line[1] == 'O' && config->no)
	{
		free(config->no);
		config->no = NULL;
		return ;
	}
	else if (line[0] == 'S' && line[1] == 'O' && config->so)
	{
		free(config->so);
		config->so = NULL;
		return ;
	}
	else if (line[0] == 'W' && line[1] == 'E' && config->we)
	{
		free(config->we);
		config->we = NULL;
		return ;
	}
	else if (line[0] == 'E' && line[1] == 'A' && config->ea)
	{
		free(config->ea);
		config->ea = NULL;
		return ;
	}
	else if (line[0] == 'S' && config->s)
	{
		free(config->s);
		config->s = NULL;
		return ;
	}
	else if (line[0] == 'F' && config->f_str)
	{
		free(config->f_str);
		config->f_str = NULL;
		return ;
	}
	else if (line[0] == 'C' && config->c_str)
	{
		free(config->c_str);
		config->c_str = NULL;
		return ;
	}
	if (line[0] == 'R')
	{
		config->width = ft_get_width(ft_strtrim(line + 1, " "));
		config->height = ft_get_height(ft_strtrim(line + 1, " "));
	}
	else if (line[0] == 'N' && line[1] == 'O')
		config->no = ft_strtrim(line + 2, " ");
	else if (line[0] == 'S' && line[1] == 'O')
		config->so = ft_strtrim(line + 2, " ");
	else if (line[0] == 'W' && line[1] == 'E')
		config->we = ft_strtrim(line + 2, " ");
	else if (line[0] == 'E' && line[1] == 'A')
		config->ea = ft_strtrim(line + 2, " ");
	else if (line[0] == 'S')
		config->s = ft_strtrim(line + 1, " ");
	else if (line[0] == 'F')
		config->f_str = ft_strtrim(line + 1, " ");
	else if (line[0] == 'C')
		config->c_str = ft_strtrim(line + 1, " ");
}

t_list		*ft_make_list_map(int fd, char *line)
{
	t_list	*head;
	t_list	*cur;
	int		r;

	if (!(head = ft_lstnew(line)))
		return (NULL);
	while ((r = get_next_line(fd, &line)) > 0)
	{
		cur = ft_lstnew(line);
		if (!cur)
		{
			ft_lstclear(&head, free);
			return (NULL);
		}
		ft_lstadd_back(&head, cur);
	}
	if (r < 0 || !(cur = ft_lstnew(line)))
	{
		ft_lstadd_back(&head, cur);
		return (NULL);
	}
	ft_lstadd_back(&head, cur);
	return (head);
}

char		**ft_convert_lst_to_matrix(t_list **lst)
{
	int		k;
	char	**map;
	t_list	*head;

	if (!(map = (char **)ft_calloc(ft_lstsize(*lst) + 1, sizeof(char *))))
		return (NULL);
	k = 0;
	head = *lst;
	while (*lst)
	{
		map[k] = ft_strdup((char *)(*lst)->content);
		if (map[k] == NULL)
		{
			while (k-- > 0)
				free(map[k]);
			free(map);
			return (NULL);
		}
		k++;
		*lst = (*lst)->next;
	}
	ft_lstclear(&head, free);
	return (map);
}

void		ft_find_person(t_vars *vars)
{
	int k;
	int j;
	int	f;

	f = FALSE;
	k = 0;
	while (vars->data.map[k])
	{
		j = 0;
		while (vars->data.map[k][j])
		{
			if (ft_strchr("NSEW", vars->data.map[k][j]))
			{
				vars->person.pos_x = k + 0.5;
				vars->person.pos_y = j + 0.5;
				vars->person.moveSpeed = 0.08;
				vars->person.rotSpeed = 0.045;
				if (vars->data.map[k][j] == 'N')
				{
					vars->person.dirX = -1;
					vars->person.dirY = 0;
					vars->person.planeX = 0;
					vars->person.planeY = 0.66;
				}
				else if (vars->data.map[k][j] == 'S')
				{
					vars->person.dirX = 1;
					vars->person.dirY = 0;
					vars->person.planeX = 0;
					vars->person.planeY = -0.66;
				}
				else if (vars->data.map[k][j] == 'E')
				{
					vars->person.dirX = 0;
					vars->person.dirY = 1;
					vars->person.planeX = 0.66;
					vars->person.planeY = 0;
				}
				else if (vars->data.map[k][j] == 'W')
				{
					vars->person.dirX = 0;
					vars->person.dirY = -1;
					vars->person.planeX = -0.66;
					vars->person.planeY = 0;
				}
				vars->data.map[k][j] = '0';
				if (f == TRUE)
				{
					vars->data.error = "Error\nFound many players";
					return ;
				}
				f = TRUE;
			}
			j++;
		}
		k++;
	}
	if (!f)
	{
		vars->data.error = "Error\nPlayer not found";
		return ;
	}
}
