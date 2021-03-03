/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:29:56 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/03 17:29:57 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_PARSER_H
# define HEAD_PARSER_H

t_window	ft_get_r(char *str);

void		ft_set_config(t_config *config, char *line);

t_list		*ft_make_list_map(int fd, char *line);

char		**ft_convert_lst_to_matrix(t_list **lst);

void		ft_find_person(t_vars *vars);

#endif