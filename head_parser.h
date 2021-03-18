/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:29:56 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/18 03:25:27 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_PARSER_H
# define HEAD_PARSER_H

int		ft_is_identifier(char *str);

void	ft_set_config(t_config *config, char *line);

int		ft_check_and_make_map(t_data *data, t_config *config, int fd, char *last_line);

void	ft_find_person(t_person *person, t_data *data);

void	ft_count_sprites(t_vars *vars);

int		ft_check_resolution(int *width, int *height, void *mlx_ptr);
int		ft_check_and_get_color(char *str, int *color);
int		ft_get_num(char *str);
char 	*ft_skip_separator(char *str);
int		ft_get_color(int num1, int num2, int num3);
int		ft_check_xpm_file(char *str);
int		ft_check_other_chars_map(char **map);
int		ft_check_empty_line_map(char **map);
int		ft_check_edges(char **map);
int		ft_check_zero(char **map);
#endif
