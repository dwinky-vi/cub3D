/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validator2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 22:05:44 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/06 22:30:40 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

int		ft_checking_map(char **map)
{
	int	k;
	int	j;

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
