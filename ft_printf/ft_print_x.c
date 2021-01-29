/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 20:33:30 by dwinky            #+#    #+#             */
/*   Updated: 2021/01/08 21:02:14 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		flag_minus(char *hex_num, int len_num, t_unit *unit, int *res)
{
	int z;

	if (unit->precision > len_num)
	{
		put_counts_char('0', unit->precision - len_num);
		*res += unit->precision - len_num;
	}
	*res += ft_putstr(hex_num);
	if (unit->width > ft_max(len_num, unit->precision))
	{
		z = unit->width - ft_max(len_num, unit->precision);
		*res += put_counts_char(' ', z);
	}
}

static void		flag_zero(char *hex_num, int len_num, t_unit *unit, int *res)
{
	if (unit->width > len_num && unit->precision > len_num)
	{
		*res += put_counts_char(' ', unit->width - unit->precision);
	}
	if (unit->precision > len_num)
	{
		*res += put_counts_char('0', unit->precision - len_num);
	}
	else if (unit->width > len_num)
	{
		*res += put_counts_char('0', unit->width - len_num);
	}
	*res += ft_putstr(hex_num);
}

static void		no_flag(char *hex_num, int len_num, t_unit *unit, int *res)
{
	if (unit->width > len_num)
		*res += put_counts_char(' ', unit->width -
										ft_max(unit->precision, len_num));
	if (unit->precision > len_num)
		*res += put_counts_char('0', unit->precision - len_num);
	*res += ft_putstr(hex_num);
}

static void		ft_toupper_hex(char *hex_num, char ch)
{
	size_t k;

	k = 0;
	if (ch == 1)
		while (hex_num[k] != '\0')
		{
			hex_num[k] = ft_toupper(hex_num[k]);
			k++;
		}
}

int				ft_print_x(t_unit *unit, unsigned int num)
{
	int		len_num;
	int		res;
	char	*hex_num;

	res = 0;
	if (unit->width == 0 && unit->precision == 0 && num == 0)
		return (0);
	else if (unit->precision == 0 && num == 0)
	{
		put_counts_char(' ', unit->width);
		return (unit->width == -1 ? 0 : unit->width);
	}
	if ((hex_num = ft_dec_to_hex(num)) == NULL)
		return (-1);
	ft_toupper_hex(hex_num, (unit->type == 'X' ? 1 : 0));
	len_num = ft_strlen(hex_num);
	if (unit->flag == '-')
		flag_minus(hex_num, len_num, unit, &res);
	else if (unit->flag == '0')
		flag_zero(hex_num, len_num, unit, &res);
	else
		no_flag(hex_num, len_num, unit, &res);
	free(hex_num);
	return (res);
}
