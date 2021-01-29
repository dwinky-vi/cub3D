/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 20:33:09 by dwinky            #+#    #+#             */
/*   Updated: 2021/01/06 21:33:10 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Если использовать флаг 0 или точность с %p компилятор говорит,
** что это неопределённое поведение. Я же просто игнорирую флаг 0 и точность,
** считая это более корректным.
*/

static int	print_only_point(char *hex_num)
{
	int		res;

	res = ft_putstr("0x");
	res += ft_putstr(hex_num);
	return (res);
}

static int	print_only_0x(char flag, int width)
{
	int	res;

	res = 0;
	if (flag != '-')
		res += put_counts_char(' ', width - (int)ft_strlen("0x"));
	res += ft_putstr("0x");
	if (flag == '-')
		res += put_counts_char(' ', width - (int)ft_strlen("0x"));
	return (res);
}

int			ft_print_p(t_unit *unit, unsigned long long num)
{
	int		res;
	char	*hex_num;

	hex_num = ft_dec_to_hex(num);
	if (hex_num == NULL)
		return (-1);
	res = 0;
	if (unit->precision == 0)
		return (print_only_0x(unit->flag, unit->width));
	if (unit->flag != '-')
		res += put_counts_char(' ', unit->width - ft_strlen("0x")
												- ft_strlen(hex_num));
	res += print_only_point(hex_num);
	if (unit->flag == '-')
		res += put_counts_char(' ', unit->width - ft_strlen("0x")
												- ft_strlen(hex_num));
	free(hex_num);
	return (res);
}
