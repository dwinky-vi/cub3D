/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 18:49:29 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/20 18:24:43 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

void		ft_set_hooks(t_vars *vars)
{
	mlx_hook(vars->win_ptr, 2, 0, key_press_hook, vars);
	mlx_hook(vars->win_ptr, 3, 0, key_release_hook, vars);
	mlx_hook(vars->win_ptr, 17, 0, exit_hook, vars);
}

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
	if (key == 123)
		vars->k_123 = TRUE;
	if (key == 124)
		vars->k_124 = TRUE;
	if (key == 257)
		vars->k_257 = TRUE;
	return (0);
}

int			key_release_hook(int key, t_vars *vars)
{
	if (key == 53)
		exit_hook(vars);
	if (key == 13)
		vars->k_13 = FALSE;
	if (key == 1)
		vars->k_1 = FALSE;
	if (key == 0)
		vars->k_0 = FALSE;
	if (key == 2)
		vars->k_2 = FALSE;
	if (key == 123)
		vars->k_123 = FALSE;
	if (key == 124)
		vars->k_124 = FALSE;
	if (key == 257)
		vars->k_257 = FALSE;
	return (0);
}

int			exit_hook(t_vars *vars)
{
	mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
	ft_putstr("Exit");
	exit(0);
}
