/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:29:21 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/14 22:33:17 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"
#include "head_parser.h"

static int	ft_is_identifier(char *str)
{
	char	*tmp;
	int		k;

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

t_vars		ft_parse_data(int fd)
{
	t_vars	vars;
	char	*line;
	char	*tmp;
	int		r;

	vars.data.error = NULL;
	ft_bzero(&vars.data.config, sizeof(vars.data.config));
	while ((r = get_next_line(fd, &line)) > 0)
	{
		tmp = line;
		line = ft_strtrim(line, " \t");
		if (ft_is_identifier(line))
		{
			ft_set_config(&vars.data.config, line);
			free(tmp);
			free(line);
			continue ;
		}
		else
			break ;
	}
	free(line);
	if (r <= 0)
	{
		vars.data.error = "Error in GNL";
		return (vars);
	}
	if (ft_check(&vars, fd, tmp))
		return (vars);
	ft_find_person(&vars);
	ft_count_sprites(&vars);
	return (vars);
}

int			ft_check(t_vars *vars, int fd, char *last_line)
{
	t_list	*list_map;

	if (!vars->data.config.so || !vars->data.config.we ||
		!vars->data.config.no ||
		!vars->data.config.ea ||
		!vars->data.config.s || !vars->data.config.f_str ||
		!vars->data.config.c_str)
	{
		vars->data.error = "Error\nIn identifier";
		return (1);
	}
	list_map = ft_make_list_map(fd, last_line);
	if (!list_map)
	{
		vars->data.error = "Error in list_map";
		return (1);
	}
	vars->data.map = ft_convert_lst_to_matrix(&list_map);
	if (!vars->data.map)
	{
		vars->data.error = "Error in malloc in map";
		return (1);
	}
	return (0);
}

void		ft_count_sprites(t_vars *vars)
{
	int count;
	int	k;
	int j;

	k = 0;
	count = 0;
	while (vars->data.map[k])
	{
		j = 0;
		while (vars->data.map[k][j])
		{
			if (vars->data.map[k][j] == '2')
				count++;
			j++;
		}
		k++;
	}
	vars->count_sprites = count;
}
