/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 15:00:46 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/21 22:12:10 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	width –– ширина
**	precision –– точность
**	was_written –– сколько всего символов было записано
**	flag '0' добавляет нули в начало числа
**	flag '-' добавляет пробелы в начало числа
*/

/*
** Точность задаётся в виде точки с последующим десятичным числом
**  или звёздочкой (*),
**  если число или звёздочка отсутствует (присутствует только точка),
**  то предполагается, что число равно нулю.
*/

#include "ft_printf.h"

static int	ft_error(va_list *ap)
{
	va_end(*ap);
	return (-1);
}

static int	ft_parse_process(va_list *ap, size_t *k, char const *comand_line)
{
	t_unit	*unit;
	int		z;

	if (*comand_line == '\0')
		return (ft_error(ap));
	if ((unit = parser(comand_line, ap)) == NULL)
		return (ft_error(ap));
	*k += unit->length;
	z = processor(unit, ap);
	if (z == -1)
		return (ft_error(ap));
	return (z);
}

int			ft_printf(const char *comand_line, ...)
{
	va_list ap;
	size_t	k;
	int		was_written;
	int		z;

	if (comand_line == NULL)
		return (-1);
	was_written = 0;
	k = 0;
	va_start(ap, comand_line);
	while (comand_line[k])
	{
		if (comand_line[k] == '%')
		{
			z = ft_parse_process(&ap, &k, comand_line + k + 1);
			if (z == -1)
				return (ft_error(&ap));
			was_written += z;
		}
		else
			was_written += ft_putchar(comand_line[k]);
		k++;
	}
	va_end(ap);
	return (was_written);
}
