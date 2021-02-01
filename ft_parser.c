#include "ft_cub3d.h"

static t_size ft_get_r(char *str)
{
	t_size	r;
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

void    ft_set_config(t_config *config, char *line)
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
        config->f = ft_strtrim(line + 1, " ");
    else if (line[0] == 'C')
        config->c = ft_strtrim(line + 1, " ");
}

t_data	ft_get_data(int fd)
{
    t_data       data;
	char		*line;
	char		*tmp;
	t_list	    *list_map;

	line = NULL;
	while (get_next_line(fd, &line))
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
	list_map = ft_make_list_map(fd, tmp);
    data.map = ft_convert_lst_to_matrix(&list_map);
	return (data);
}

t_list		*ft_make_list_map(int fd, char *line)
{
    t_list *head;

    head = ft_lstnew(line);
	while (get_next_line(fd, &line))
		ft_lstadd_back(&head, ft_lstnew(line));
	ft_lstadd_back(&head, ft_lstnew(line));
    return (head);
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
