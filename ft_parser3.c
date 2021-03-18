/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:56:00 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/18 03:26:25 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"
#define ERROR06 "Error\n06 Some identifiers are missing or dublicated\n"
#define ERROR07 "Error\n07 Problem in ft_make_list_map\n"
#define ERROR08 "Error\n08 Problem malloc, when converting list to an array\n"

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

int			ft_check_file_cub(char *str)
{
	int k;
	
	k = 0;
	while (str[k])
	{
		if (str[k] == '.' && str[k + 1] == 'c' && str[k + 2] == 'u' &&
			str[k + 3] == 'b' && str[k + 4] == '\0')
			return (open(str, O_RDONLY));
		k++;
	}
	return (-1);

}