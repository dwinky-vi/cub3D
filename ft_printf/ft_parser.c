/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 20:30:39 by dwinky            #+#    #+#             */
/*   Updated: 2021/01/09 15:01:03 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	printf("%t", 1); –– это невалидный случай.
**	Если после процента (также после флагов, ширины и точности)
**	не стоит валидный спецификатор, то моя функция прекращает свою работу
**	и возвращает -1.
*/

#include "ft_printf.h"

static char	check_type(char type)
{
	if (type == '\0')
		return (0);
	if (type != 'c' && type != 's' && type != 'p' && type != 'd' &&
	type != 'i' && type != 'u' && type != 'x' && type != 'X' && type != '%')
		return (0);
	else
		return (type);
}

static void	cancel_flag_zero_with_precision(t_unit *unit)
{
	char type;

	type = unit->type;
	if (unit->flag == '0' && unit->precision >= 0 && (type == 'd' ||
	type == 'i' || type == 'u' || type == 'x' || type == 'X'))
		unit->flag = 0;
}

static void	cansel_flag_zero(t_unit *unit)
{
	if (unit->flag == '0' &&
		(unit->type == 'c' || unit->type == 's' || unit->type == 'p'))
		unit->flag = 0;
}

t_unit		*parser(char const *str, va_list *ap)
{
	int		k;
	t_unit	*unit;

	if ((unit = creat_new_unit()) == NULL)
		return (NULL);
	k = 0;
	unit->flag = which_flag(str, &k);
	parse_width(ap, unit, &k, str);
	parse_precision(ap, unit, &k, str);
	if ((unit->type = check_type(str[k])) == 0)
		return (NULL);
	k++;
	unit->length = k;
	cancel_flag_zero_with_precision(unit);
	cansel_flag_zero(unit);
	return (unit);
}
