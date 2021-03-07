/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2d_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:05:06 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/07 14:10:39 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_3d.h"
#include "head_2d.h"

void		set_hooks_2(t_vars *vars)
{
	vars->k_0 = FALSE;
	vars->k_1 = FALSE;
	vars->k_2 = FALSE;
	vars->k_13 = FALSE;
	mlx_hook(vars->win_ptr, 2, 0, key_press_hook, vars);
	mlx_hook(vars->win_ptr, 3, 0, key_release_hook_2, vars);
	mlx_hook(vars->win_ptr, 17, 0, exit_hook, vars);
}

void		ft_step(t_vars *vars)
{
	if (vars->k_13)
	{
		if (vars->k_0)
			vars->person.dir += 0.03;
		else if (vars->k_2)
			vars->person.dir -= 0.03;
		vars->person.x += cos(vars->person.dir) * 0.03;
		vars->person.y += sin(vars->person.dir) * 0.03;
	}
	if (vars->k_1)
	{
		if (vars->k_0)
			vars->person.dir += 0.03;
		else if (vars->k_2)
			vars->person.dir -= 0.03;
		vars->person.x -= cos(vars->person.dir) * 0.03;
		vars->person.y -= sin(vars->person.dir) * 0.03;
	}
	if (vars->k_0)
		vars->person.dir += 0.03;
	if (vars->k_2)
		vars->person.dir -= 0.03;
}

int			ft_func(t_vars *vars)
{
	ft_step(vars);
	ft_display_map(vars);
	return (0);
}
