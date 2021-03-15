/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:29:42 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/15 16:37:24 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"
#include "head_parser.h"

#define ERROR06 "Error 06\n Some identifiers are missing or dublicated\n"
#define ERROR07 "Error 07\n Problem in ft_make_list_map\n"
#define ERROR08 "Error 08\n Problem in malloc when converting list to an array\n"

int			ft_is_identifier(char *str)
{
	if (*str == '\0')
		return (1);
	if (str[0] == 'R' && (str[1] == ' ' || str[1] == '\t'))
		return (1);
	if (str[0] == 'S' && (str[1] == ' ' || str[1] == '\t'))
		return (1);
	if (str[0] == 'F' && (str[1] == ' ' || str[1] == '\t'))
		return (1);
	if (str[0] == 'C' && (str[1] == ' ' || str[1] == '\t'))
		return (1);
	if (str[0] == 'N' && str[1] == 'O' && (str[2] == ' ' || str[2] == '\t'))
		return (1);
	if (str[0] == 'S' && str[1] == 'O' && (str[2] == ' ' || str[2] == '\t'))
		return (1);
	if (str[0] == 'W' && str[1] == 'E' && (str[2] == ' ' || str[2] == '\t'))
		return (1);
	if (str[0] == 'E' && str[1] == 'A' && (str[2] == ' ' || str[2] == '\t'))
		return (1);
	return (0);
}

int			ft_free_and_put_null(char **data)
{
	free(*data);
	*data = NULL;
	return (1);
}

int		ft_is_dublicate_id(t_config *config, char *line)
{
	if (line[0] == 'R' && config->width != 0)
	{
		config->width = -12;
		config->height = -13;
		return (1);
	}
	else if (line[0] == 'N' && line[1] == 'O' && config->no)
		return (ft_free_and_put_null(&config->no));
	else if (line[0] == 'S' && line[1] == 'O' && config->so)
		return (ft_free_and_put_null(&config->so));
	else if (line[0] == 'W' && line[1] == 'E' && config->we)
		return (ft_free_and_put_null(&config->we));
	else if (line[0] == 'E' && line[1] == 'A' && config->ea)
		return (ft_free_and_put_null(&config->ea));
	else if (line[0] == 'S' && config->s)
		return (ft_free_and_put_null(&config->s));
	else if (line[0] == 'F' && config->f_str)
		return (ft_free_and_put_null(&config->f_str));
	else if (line[0] == 'C' && config->c_str)
		return (ft_free_and_put_null(&config->c_str));
	return (0);
}

void		ft_set_config(t_config *config, char *line)
{
	if (ft_is_dublicate_id(config, line))
		return ;
	if (line[0] == 'R')
	{
		config->width = ft_get_width(ft_strtrim(line + 1, " \t"));
		config->height = ft_get_height(ft_strtrim(line + 1, " \t"));
	}
	else if (line[0] == 'N' && line[1] == 'O')
		config->no = ft_strtrim(line + 2, " \t");
	else if (line[0] == 'S' && line[1] == 'O')
		config->so = ft_strtrim(line + 2, " \t");
	else if (line[0] == 'W' && line[1] == 'E')
		config->we = ft_strtrim(line + 2, " \t");
	else if (line[0] == 'E' && line[1] == 'A')
		config->ea = ft_strtrim(line + 2, " \t");
	else if (line[0] == 'S')
		config->s = ft_strtrim(line + 1, " \t");
	else if (line[0] == 'F')
		config->f_str = ft_strtrim(line + 1, " \t");
	else if (line[0] == 'C')
		config->c_str = ft_strtrim(line + 1, " \t");
}

int	ft_get_width(char *str)
{
	int	width;

	width = ft_atoi(str);
	free(str);
	if (width == 0)
		width = -12;
	return (width);
}

int	ft_get_height(char *str)
{
	char	*tmp;
	int		height;

	tmp = str;
	while (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str))
		str++;
	height = ft_atoi(str);
	free(tmp);
	if (height == 0)
		height = -13;
	return (height);
}

int			ft_check_and_make_map(t_vars *vars, int fd, char *last_line)
{
	t_list	*list_map;

	if (!vars->data.config.so || !vars->data.config.we ||
		!vars->data.config.no || vars->data.config.width == -1 ||
		!vars->data.config.ea ||
		!vars->data.config.s || !vars->data.config.f_str ||
		!vars->data.config.c_str)
	{
		vars->data.error = ERROR06;
		return (1);
	}
	list_map = ft_make_list_map(fd, last_line);
	if (!list_map)
	{
		vars->data.error = ERROR07;
		return (1);
	}
	vars->data.map = ft_convert_lst_to_matrix(&list_map);
	if (!vars->data.map)
	{
		vars->data.error = ERROR08;
		return (1);
	}
	return (0);
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

