/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 20:53:53 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/06 22:08:58 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

void	ft_free_map(char **map)
{
	int	k;

	k = 0;
	while (map[k])
	{
		free(map[k]);
		k++;
	}
	free(map);
}

void	ft_free_config(t_config *conf)
{
	free(conf->no);
	free(conf->so);
	free(conf->we);
	free(conf->ea);
	free(conf->s);
	free(conf->f_str);
	free(conf->c_str);
}
