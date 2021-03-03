/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:29:42 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/03 18:07:20 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"
#include "head_parser.h"

t_window ft_get_r(char *str)
{
	t_window	r;
    char    	*tmp;

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
	if (line[0] == 'R' && config->r.size_x != 0)
	{
		config->r.size_x = 0;
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

void			ft_find_person(t_vars *vars)
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
				vars->person.x = k + 0.5;
				vars->person.y = j + 0.5;
				vars->person.start = 0;
				vars->person.end = 0;
				vars->person.dir = M_PI;
				vars->data.map[k][j] = '0';
				// ft_putstr("k = ");
				// ft_putnbr((int)vars->person.x);
				// ft_putchar('\n');
				// ft_putstr("j = ");
				// ft_putnbr((int)vars->person.y);
				// ft_putchar('\n');
				// ft_putstr("dir = ");
				// ft_putnbr((int)vars->person.dir);
				// ft_putchar('\n');
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