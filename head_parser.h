#ifndef HEAD_PARSER_H
# define HEAD_PARSER_H

t_window	ft_get_r(char *str);

void		ft_set_config(t_config *config, char *line);

t_list		*ft_make_list_map(int fd, char *line);

char		**ft_convert_lst_to_matrix(t_list **lst);

void		ft_find_person(t_vars *vars);

#endif