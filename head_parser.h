/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:29:56 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/15 15:55:04 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_PARSER_H
# define HEAD_PARSER_H

void	ft_set_config(t_config *config, char *line);

int	ft_is_identifier(char *str);

int	ft_get_width(char *str);
int	ft_get_height(char *str);
t_list	*ft_make_list_map(int fd, char *line);

char	**ft_convert_lst_to_matrix(t_list **lst);

void	ft_find_person(t_person *person, t_data *data);

void	ft_count_sprites(t_vars *vars);

int		ft_check_and_make_map(t_vars *vars,	int fd,	char *last_line);

#endif
