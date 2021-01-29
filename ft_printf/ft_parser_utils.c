/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 13:24:50 by dwinky            #+#    #+#             */
/*   Updated: 2021/01/08 18:57:30 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		which_flag(char const *str, int *k)
{
	char	flag;
	int		k2;

	k2 = *k;
	flag = 0;
	while (str[k2] == '-' || str[k2] == '0')
	{
		if (str[k2] == '-')
			flag = '-';
		else if (str[k2] == '0' && flag != '-')
			flag = '0';
		k2++;
	}
	*k = k2;
	return (flag);
}

void		parse_width(va_list *ap, t_unit *unit, int *k, const char *str)
{
	int	k2;

	k2 = *k;
	if (str[k2] == '*')
	{
		unit->width = va_arg(*ap, int);
		if (unit->width < 0)
		{
			unit->flag = '-';
			unit->width *= -1;
		}
		k2++;
	}
	else if (ft_isdigit(str[k2]))
	{
		unit->width = ft_atoi(str + k2);
		k2 += len_of_num(str + k2);
	}
	*k = k2;
}

void		parse_precision(va_list *ap, t_unit *unit, int *k, char const *str)
{
	int k2;

	k2 = *k;
	if (str[k2] == '.')
	{
		k2++;
		if (str[k2] == '*')
		{
			unit->precision = va_arg(*ap, int);
			unit->precision = (unit->precision < 0 ? -1 : unit->precision);
			k2++;
		}
		else if (ft_isdigit(str[k2]))
		{
			unit->precision = ft_atoi(str + k2);
			k2 += len_of_num(str + k2);
		}
		else
			unit->precision = 0;
	}
	*k = k2;
}
