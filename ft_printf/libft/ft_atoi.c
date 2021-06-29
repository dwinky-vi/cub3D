/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:59:43 by dwinky            #+#    #+#             */
/*   Updated: 2020/11/03 17:17:40 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	k;

	k = 0;
	sign = 1;
	result = 0;
	while ((9 <= str[k] && str[k] <= 13) || str[k] == 32)
		k++;
	if (ft_strncmp("-2147483648", str, 11) == 0)
		return (-2147483648);
	if (str[k] == '-')
	{
		sign = -1;
		k++;
	}
	else if (str[k] == '+')
		k++;
	while (ft_isdigit(str[k]))
	{
		result *= 10;
		result += str[k] - '0';
		k++;
	}
	return (sign * result);
}
