/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:29:21 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/18 05:53:38 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"
#include "head_parser.h"
#define ERROR04 "Error\n04 Promlen in malloc\n"
#define ERROR05 "Error\n05 Problem in GNL\n"

static t_vars	*ft_error(t_vars *vars, char *error)
{
	vars->data.error = error;
	return (vars);
}

static void		ft_patch(t_config *config, char *line, char *tmp)
{
	ft_set_config(config, line);
	free(tmp);
	free(line);
}

/*
** 		_____main function_____
*/

t_vars			ft_parse_data(int fd)
{
	t_vars	vars;
	char	*line;
	char	*tmp;
	int		r;

	ft_bzero(&vars, sizeof(vars));
	while ((r = get_next_line(fd, &line)) > 0)
	{
		tmp = line;
		line = ft_strtrim(line, " ");
		if (line == NULL)
			return (*ft_error(&vars, ERROR04));
		if (ft_is_identifier(line))
			ft_patch(&vars.data.config, line, tmp);
		else
			break ;
	}
	if (r <= 0)
		return (*ft_error(&vars, ERROR05));
	free(line);
	if (ft_check_and_make_map(&vars.data, &vars.data.config, fd, tmp))
		return (vars);
	ft_find_person(&vars.person, &vars.data);
	ft_count_sprites(&vars);
	return (vars);
}
