/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validator4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 22:05:44 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/18 03:12:08 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

int		ft_check_xpm_file(char *str)
{
	int		fd;
	size_t	len;

	len = ft_strlen(str);
	if (str[len - 4] != '.' || str[len - 3] != 'x' ||
		str[len - 2] != 'p' || str[len - 1] != 'm')
		return (1);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (1);
	else
		close(fd);
	return (0);
}

int		ft_check_other_chars_map(char **map)
{
	size_t	k;
	size_t	j;

	k = 0;
	while (map[k])
	{
		j = 0;
		while (map[k][j])
		{
			if (!(ft_strchr("012 \nNSWE", map[k][j])))
				return (1);
			j++;
		}
		k++;
	}
	return (0);
}

int		ft_check_empty_line_map(char **map)
{
	size_t	k;

	k = 0;
	while (map[k])
	{
		if (map[k][0] == '\0')
			return (1);
		k++;
	}
	return (0);
}

int		ft_check_edges(char **map)
{
	size_t	k;
	size_t	l;
	char	*tmp;

	if (ft_strrchr(map[0], '0') || ft_strrchr(map[0], '2'))
		return (1);
	k = 0;
	while (map[k])
	{
		tmp = ft_strtrim(map[k], " ");
		l = ft_strlen(tmp) - 1;
		if (tmp[0] == '0' || tmp[l] == '0' || tmp[0] == '2' || tmp[l] == '2')
		{
			free(tmp);
			return (1);
		}
		free(tmp);
		k++;
	}
	k--;
	if (ft_strrchr(map[k], '0') || ft_strrchr(map[k], '2'))
		return (1);
	return (0);
}

int		ft_check_zero(char **map)
{
	size_t	k;
	size_t	j;

	k = 1;
	while (map[k])
	{
		j = 1;
		while (map[k][j])
		{
			if (map[k][j] == '0' || map[k][j] == '2')
			{
				if (ft_strlen(map[k - 1]) - 1 < j)
					return (1);
				if (ft_strlen(map[k + 1]) - 1 < j)
					return (1);
				if (map[k][j - 1] == ' ' || map[k][j + 1] == ' ' ||
					map[k - 1][j] == ' ' || map[k + 1][j] == ' ')
					return (1);
			}
			j++;
		}
		k++;
	}
	return (0);
}
