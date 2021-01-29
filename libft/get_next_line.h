/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 21:59:52 by dwinky            #+#    #+#             */
/*   Updated: 2021/01/29 15:44:18 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

void	*ft_calloc(size_t number, size_t size);

int		ft_error(char **str, char *str2);

void	ft_clear_tail(char **s_tail);

size_t	ft_strlen(const char *str);

char	*ft_strchr(char *str, int c);

char	*ft_strdup(const char *str);

char	*ft_strjoin_to_new_line_and_free(char **s1, char *s2);

int		check_tail(char **line, char **s_tail, char **find_end);

int		set_line(char **array, char **s_tail, char **find_end);

int		get_next_line(int fd, char **line);

#endif
