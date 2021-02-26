/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:54:26 by dwinky            #+#    #+#             */
/*   Updated: 2021/02/18 20:46:14 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUB3D_H
# define FT_CUB3D_H 

# include "head_structs.h"
# include "head_2d.h"
# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"
# include "./minilibx/mlx.h"
# include <fcntl.h>
# include <math.h>

void    my_mlx_pixel_put(t_img *data, int x, int y, int color);

// int	    ft_puterror(char *str);

void	ft_lstprint_ass_str(t_list **list);

void	ft_print_map(char **map);

void	ft_print_config(t_config config);

void	ft_free_map(char **map);

void	ft_free_config(t_config *conf);

t_vars	ft_parse_data(int fd);

char    *ft_validator(t_data *data);

#endif
