/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validator3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 03:08:12 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/18 05:40:19 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

int		ft_get_num(char *str)
{
	int	k;
	int num;

	if (*str == '+')
		str++;
	if (!ft_isdigit(str[0]))
		return (-1);
	if (str[0] == '0' && ft_isdigit(str[1]))
		return (-1);
	num = ft_atoi(str);
	k = 0;
	while (ft_isdigit(str[k]))
		k++;
	if (k > 3 || 255 < num || num < 0)
		return (-1);
	return (num);
}

char	*ft_skip_separator(char *str)
{
	if (*str == '+')
		str++;
	while (ft_isdigit(*str))
		str++;
	if (*str != ' ' && *str != ',')
		return (NULL);
	if (*str == ',')
		str++;
	while (*str == ' ')
		str++;
	return (str);
}

int		ft_get_color(int num1, int num2, int num3)
{
	int	color;

	color = 0;
	color = color | num1;
	color = color << 8;
	color = color | num2;
	color = color << 8;
	color = color | num3;
	return (color);
}
