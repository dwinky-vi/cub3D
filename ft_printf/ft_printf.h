/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 15:00:51 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/21 22:08:42 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "./libft/libft.h"
# include <stdarg.h>

typedef struct	s_unit
{
	char		flag;
	int			width;
	int			precision;
	char		type;
	int			length;
}				t_unit;

int				ft_printf(const char *comand_line, ...);

t_unit			*parser(char const *str, va_list *ap);

char			which_flag(char const *str, int *k);

void			parse_width(va_list *ap, t_unit *unit, int *k, const char *s);

void			parse_precision(va_list *ap, t_unit *u, int *k, char const *s);

int				processor(t_unit *unit, va_list *ap);

t_unit			*creat_new_unit(void);

void			print_unit(t_unit *unit);

size_t			len_of_num(char const *str);

size_t			len_of_num2(long long nbr);

int				put_counts_char(char ch, int count);

char			*ft_dec_to_hex(unsigned long long nbr);

int				ft_print_c(t_unit *unit, int ch);

int				ft_print_d(t_unit *unit, int num);

int				ft_print_p(t_unit *unit, unsigned long long num);

int				ft_print_s(t_unit *unit, unsigned char *str);

int				ft_print_u(t_unit *unit, unsigned int num);

int				ft_print_x(t_unit *unit, unsigned int num);

int				ft_print_percent(t_unit *unit);

#endif
