/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_2d.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:29:53 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/07 14:02:31 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_2D_H
# define HEAD_2D_H

void	set_hooks_2(t_vars *vars);

int		ft_func(t_vars *vars);

void	ft_step(t_vars *vars);

void	ft_cast_rays(t_vars *vars);

void	ft_draw_pixel(t_vars *vars, t_point start, t_point end, int color);

int		ft_init_img(void *mlx_ptr, t_img *img, t_config *config)

void	ft_display_map(t_vars *vars);

#endif
