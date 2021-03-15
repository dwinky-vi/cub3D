/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:29:56 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/15 18:33:58 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_PARSER_H
# define HEAD_PARSER_H

int		ft_is_identifier(char *str);

void	ft_set_config(t_config *config, char *line);

int		ft_check_and_make_map(t_data *data, t_config *config, int fd, char *last_line);

void	ft_find_person(t_person *person, t_data *data);

void	ft_count_sprites(t_vars *vars);

#endif
