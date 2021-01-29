/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_unit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 21:22:02 by dwinky            #+#    #+#             */
/*   Updated: 2021/01/09 15:59:48 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_unit	*creat_new_unit(void)
{
	t_unit *new_unit;

	new_unit = (t_unit *)ft_calloc(1, sizeof(t_unit));
	if (new_unit == NULL)
		return (NULL);
	new_unit->width = -1;
	new_unit->precision = -1;
	return (new_unit);
}
