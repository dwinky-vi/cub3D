/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:29:42 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/15 18:24:58 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

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

static int	ft_free_and_put_null(char **data)
{
	free(*data);
	*data = NULL;
	return (1);
}

static int	ft_is_dublicate_id(t_config *config, char *line)
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

static void	ft_get_w_h(char *str, int *w, int *h)
{
	char	*tmp;
	int		height;
	int		width;

	tmp = str;
	width = ft_atoi(str);
	if (width == 0)
		width = -12;
	while (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str))
		str++;
	height = ft_atoi(str);
	free(tmp);
	if (height == 0)
		height = -13;
	*w = width;
	*h = height;
}

void		ft_set_config(t_config *config, char *line)
{
	if (ft_is_dublicate_id(config, line))
		return ;
	if (line[0] == 'R')
		ft_get_w_h(ft_strtrim(++line, " \t"), &config->width, &config->height);
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
