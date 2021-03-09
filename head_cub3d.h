/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_cub3d.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:54:26 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/09 21:54:43 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_CUB3D_H
# define HEAD_CUB3D_H

# include "head_structs.h"
# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"

# include "./minilibx_c/mlx.h"
# include <fcntl.h>
# include <math.h>

/*
** utils
*/

int		ft_puterror(char *str);

void	ft_lstprint_ass_str(t_list **list);

void	ft_print_map(char **map);

void	ft_print_config(t_config config);

void	ft_free_map(char **map);

void	ft_free_config(t_config *conf);

/*
** raycast
*/

int		ft_raycast(t_vars *vars);

void	generete_textures(int texWidth, int texHeight, int texture[8][texWidth * texHeight]);

void	ft_calculate_distance(t_sprite *sprite, char **map,
								double pos_x, double pos_y);

void	ft_spritecasting(t_vars *vars, double pos_x, double pos_y,
							double *ZBuffer);

int		get_color_wall(t_vars *vars, double texX, double texY, int stepX,
						int stepY, int side);

/*
** parser
*/

t_vars	ft_parse_data(int fd);

char	*ft_validator(t_data *data, void *mlx_ptr);

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

unsigned
int		ft_mlx_get_color(t_texture *data, int x, int y);

/*
** validator
*/

int		ft_checking_map(char **map);

/*
** движения и повороты
*/

void	make_step_forward(char **map, t_person *person, float speed);

void	make_step_back(char **map, t_person *person);

void	make_step_left(char **map, t_person *person);

void	make_step_right(char **map, t_person *person);

void	make_rotation_left(char **map, t_person *person);

void	make_rotation_right(char **map, t_person *person);

int		make_step(t_vars *vars);

/*
** hooks
*/

int		key_press_hook(int key, t_vars *vars);

int		key_release_hook(int key, t_vars *vars);

int		exit_hook(int key, t_vars *vars);

#endif
