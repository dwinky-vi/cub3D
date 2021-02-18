#include "ft_cub3d.h"

static t_window ft_get_r(char *str)
{
	t_window	r;
    char    *tmp;

    tmp = str;
	r.size_x = ft_atoi(str);
	while (ft_isdigit(*str))
		str++;
	while (!ft_isdigit(*str))
		str++;
	r.size_y = ft_atoi(str);
    free(tmp);
	return (r);
}

static void    ft_set_config(t_config *config, char *line)
{
    if (line[0] == 'R')
        config->r = ft_get_r(ft_strtrim(line + 1, " "));
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

t_data	ft_get_data(int fd)
{
    t_data      data;
	char		*line;
	char		*tmp;
	t_list	    *list_map;
	int			r;

	line = NULL;
	data.error = NULL;
	while ((r = get_next_line(fd, &line)) > 0)
	{
		tmp = line;
		line = ft_strtrim(line, " ");
        if (ft_strchr("RNOSOWEEASFC", line[0]))
        {
            ft_set_config(&(data.config), line);
            free(tmp);
            free(line);
            continue;
        }
		else
			break ;
	}
	free(line);
	if (r <= 0)
	{
		data.error = "Error in GNL";
		return (data);
	}
	list_map = ft_make_list_map(fd, tmp);
	if (!list_map)
	{
		data.error = "Error in list_map";
		return (data);
	}
    data.map = ft_convert_lst_to_matrix(&list_map);
	if (!(data.map))
	{
		data.error = "Error in malloc in map";
		return (data);
	}
	return (data);
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

char	**ft_convert_lst_to_matrix(t_list **lst)
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
