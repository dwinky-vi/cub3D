/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:55:03 by dwinky            #+#    #+#             */
/*   Updated: 2021/01/08 21:14:36 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

# ifndef INT_MAX
#  define INT_MAX  (int)2147483647
# endif

# ifndef INT_MIN
#  define INT_MIN  (int)-2147483648
# endif

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

void				*ft_memset(void *b, int c, size_t num);

void				ft_bzero(void *s, size_t num);

void				*ft_memcpy(void *dst, const void *src, size_t num);

void				*ft_memccpy(void *dst, const void *src, int c, size_t num);

void				*ft_memmove(void *dst, const void *src, size_t size);

void				*ft_memchr(const void *s, int c, size_t n);

int					ft_memcmp(const void *s1, const void *s2, size_t n);

size_t				ft_strlen(const char *str);

size_t				ft_strlcpy(char *dst, const char *src, size_t size);

size_t				ft_strlcat(char *dst, const char *srs, size_t size);

char				*ft_strchr(const char *str, int c);

char				*ft_strrchr(const char *str, int c);

char				*ft_strnstr(const char *s1, const char *s2, size_t size);

int					ft_strncmp(const char *s1, const char *s2, size_t num);

int					ft_atoi(const char *str);

char				*ft_strdup(const char *str);

void				*ft_calloc(size_t number, size_t size);

int					ft_isalpha(int ch);

int					ft_isdigit(int ch);

int					ft_isalnum(int ch);

int					ft_isascii(int ch);

int					ft_isprint(int ch);

int					ft_toupper(int ch);

int					ft_tolower(int ch);

char				*ft_substr(char const *s, unsigned int start, size_t len);

char				*ft_strjoin(char const *s1, char const *s2);

char				*ft_strtrim(char const *s1, char const *set);

char				**ft_split(char const *s, char c);

char				*ft_itoa(int n);

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void				ft_putchar_fd(char c, int fd);

size_t				ft_putchar(int c);

void				ft_putstr_fd(char *s, int fd);

size_t				ft_putstr(char *s);

void				ft_putendl_fd(char *s, int fd);

void				ft_putnbr_fd(int n, int fd);

void				ft_putnbr(int n);

void				ft_putnbr_u_int(unsigned int n);

typedef	struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);

int					ft_lstsize(t_list *lst);

t_list				*ft_lstlast(t_list *lst);

void				ft_lstadd_front(t_list **lst, t_list *new_node);

void				ft_lstadd_back(t_list **lst, t_list *new_node);

void				ft_lstiter(t_list *lst, void (*f)(void *));

void				ft_lstdelone(t_list *lst, void (*del)(void *));

void				ft_lstclear(t_list **lst, void (*del)(void *));

t_list				*ft_lstmap(t_list *lst,
								void *(*f)(void *),
								void (*del)(void *));

long long			ft_max(long long x, long long y);

long long			ft_min(long long x, long long y);

int					ft_isspace(int c);

void				ft_swap(long long *x, long long *y);

int					ft_abs(int nbr);

long long			ft_abs_ll(long long nbr);

#endif
