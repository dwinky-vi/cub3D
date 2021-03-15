/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:29:21 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/15 21:43:58 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"
#include "head_parser.h"
#define ERROR04 "Error\n04 Promlen in malloc\n"
#define ERROR05 "Error\n05 Problem in GNL\n"

/*
** 		_____main function_____
*/

t_vars		ft_parse_data(int fd)
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
		{
			vars.data.error = ERROR04;
			return (vars);
		}
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
		vars.data.error = ERROR05;
		return (vars);
	}
	if (ft_check_and_make_map(&vars.data, &vars.data.config, fd, tmp))
		return (vars);
	ft_find_person(&vars.person, &vars.data);
	ft_count_sprites(&vars);
	return (vars);
}
