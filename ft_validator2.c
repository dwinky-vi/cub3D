/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validator2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 22:05:44 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/16 23:02:52 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

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
			{
				ft_putchar(map[k][j - 1]);
				return (1);
			}
			j++;
		}
		k++;
	}
	return (0);
}

int ft_check_empty_line_map(char **map)
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

// int		ft_check_spaces_new_lines(char **map)
// {
// 	size_t	k;
// 	size_t	j;

// 	k = 0;
// 	// while (map[k])
// 	// {
// 	// 	j = 0;
// 	// 	while (map[k][j])
// 	// 	{
// 	// 		if (map[k][j] == ' ' && (map[k][j + 1] == '0' || (j != 0 && map[k][j - 1] == '0')))
// 	// 			return (1);
// 	// 		j++;
// 	// 	}
// 	// 	k++;
// 	// }
// 	return (0);
// }

int		ft_check_edges(char **map)
{
	size_t	k;
	size_t	l;

	if (ft_strrchr(map[0], '0') || ft_strrchr(map[0], '2'))
		return (1);
	k = 0;
	while (map[k])
	{
		char *tmp = ft_strtrim(map[k], " ");
		l = ft_strlen(tmp) - 1;
		if (tmp[0] == '0' || tmp[l] == '0' || tmp[0] == '2' || tmp[l] == '2')
		{
			free(tmp);
			return (1);
		}
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
				int len;
				len = ft_strlen(map[k - 1]);
				if (len - 1 < j)
				{
					ft_putstr(map[k]);
					return (1);
				}
				len = ft_strlen(map[k + 1]);
				if (len - 1 < j)
				{
					ft_putstr(map[k]);
					return (1);
				}
				if (map[k][j - 1] == ' ' || map[k][j + 1] == ' ' || map[k - 1][j] == ' ' || map[k + 1][j] == ' ')
					return (1);
			}
			j++;
		}
		k++;
	}
	return (0);
}

// пробел в конце строчки у карты???? то есть пробел за картой