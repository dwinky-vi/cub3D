/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:29:42 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/18 06:03:48 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"
#include "head_parser.h"
#define ERROR06 "Error\n06 Some identifiers are missing or dublicated\n"
#define ERROR07 "Error\n07 Problem in ft_make_list_map\n"
#define ERROR08 "Error\n08 Problem malloc, when converting list to an array\n"

int				ft_is_identifier(char *str)
{
	if (*str == '\0')
		return (1);
	if (str[0] == 'R' && str[1] == ' ')
		return (1);
	if (str[0] == 'S' && str[1] == ' ')
		return (1);
	if (str[0] == 'F' && str[1] == ' ')
		return (1);
	if (str[0] == 'C' && str[1] == ' ')
		return (1);
	if (str[0] == 'N' && str[1] == 'O' && str[2] == ' ')
		return (1);
	if (str[0] == 'S' && str[1] == 'O' && str[2] == ' ')
		return (1);
	if (str[0] == 'W' && str[1] == 'E' && str[2] == ' ')
		return (1);
	if (str[0] == 'E' && str[1] == 'A' && str[2] == ' ')
		return (1);
	return (0);
}

void			ft_set_config(t_config *config, char *line)
{
	if (ft_is_dublicate_id(config, line))
		return ;
	if (line[0] == 'R')
		ft_get_w_h(ft_strtrim(++line, " "), &config->width, &config->height);
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

static t_list	*ft_make_list_map(int fd, char *line)
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

static char		**ft_convert_lst_to_matrix(t_list **lst)
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
			while (--k >= 0)
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

int				ft_check_and_make_map(t_data *data, t_config *config,
													int fd,
													char *last_line)
{
	t_list	*list_map;

	if (!config->so || !config->we || !config->no || config->width == -1 ||
		!config->ea || !config->s || !config->f_str || !config->c_str)
	{
		data->error = ERROR06;
		return (1);
	}
	list_map = ft_make_list_map(fd, last_line);
	if (!list_map)
	{
		data->error = ERROR07;
		return (1);
	}
	data->map = ft_convert_lst_to_matrix(&list_map);
	if (!data->map)
	{
		data->error = ERROR08;
		return (1);
	}
	return (0);
}
