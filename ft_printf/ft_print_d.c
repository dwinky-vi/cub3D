/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 21:45:39 by dwinky            #+#    #+#             */
/*   Updated: 2021/01/06 20:03:23 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	flag_minus(int num, int len_num, t_unit *unit, int *res)
{
	int z;

	if (num < 0)
		*res += ft_putchar('-');
	if (unit->precision > len_num)
		*res += put_counts_char('0', unit->precision - len_num);
	ft_putnbr_u_int(ft_abs_ll(num));
	*res += len_num;
	if (unit->width > ft_max(len_num, unit->precision))
	{
		z = unit->width - ft_max(len_num, unit->precision) - (num < 0 ? 1 : 0);
		*res += put_counts_char(' ', z);
	}
}

static void	flag_zero(int num, int len_num, t_unit *unit, int *res)
{
	if (unit->width > len_num && unit->precision > len_num)
		*res += put_counts_char(' ', unit->width - unit->precision);
	if (num < 0)
		ft_putchar('-');
	if (unit->precision > len_num)
		*res += put_counts_char('0', unit->precision - len_num);
	else if (unit->width > len_num)
	{
		put_counts_char('0', unit->width - len_num - (num < 0 ? 1 : 0));
		*res += (unit->width - len_num);
	}
	ft_putnbr_u_int(ft_abs_ll(num));
	*res += len_num;
	if (unit->width <= len_num && num < 0)
		(*res)++;
}

static void	no_flag(int num, int len_num, t_unit *unit, int *res)
{
	if (num < 0)
		(unit->width)--;
	if (unit->width > len_num)
		*res += put_counts_char(' ', unit->width -
										ft_max(unit->precision, len_num));
	if (num < 0)
		*res += ft_putchar('-');
	if (unit->precision > len_num)
		*res += put_counts_char('0', unit->precision - len_num);
	ft_putnbr_u_int(ft_abs_ll(num));
	*res += len_num;
}

int			ft_print_d(t_unit *unit, int num)
{
	int len_num;
	int	res;

	res = 0;
	len_num = len_of_num2(num);
	if (unit->width == 0 && unit->precision == 0 && num == 0)
		return (0);
	else if (unit->precision == 0 && num == 0)
	{
		put_counts_char(' ', unit->width);
		return (unit->width == -1 ? 0 : unit->width);
	}
	if (unit->flag == '-')
		flag_minus(num, len_num, unit, &res);
	else if (unit->flag == '0')
		flag_zero(num, len_num, unit, &res);
	else
		no_flag(num, len_num, unit, &res);
	return (res);
}
