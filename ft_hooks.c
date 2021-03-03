/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 18:49:29 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/03 18:50:01 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int			key_press_hook(int key, t_vars *vars)
{
	if (key == 13)
		vars->k_13 = TRUE;
	if (key == 1)
		vars->k_1 = TRUE;
	if (key == 0)
		vars->k_0 = TRUE;
	if (key == 2)
		vars->k_2 = TRUE;
	return (0);
}

int			key_release_hook(int key, t_vars *vars)
{
	if (key == 53)
		exit(0);
	if (key == 13)
		vars->k_13 = FALSE;
	if (key == 1)
		vars->k_1 = FALSE;
	if (key == 0)
		vars->k_0 = FALSE;
	if (key == 2)
		vars->k_2 = FALSE;
	return (0);
}

int			exit_hook(int key, void *vars)
{
	ft_putstr("Exit");
	exit(0);
}