/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validator3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 03:08:12 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/18 03:13:00 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

int		ft_check_len_nums(char *str)
{
	int len;

	len = 0;
	while (ft_isdigit(*str))
	{
		len++;
		str++;
	}
	if (len > 3)
		return (1);
	while (!ft_isdigit(*str))
		str++;
	len = 0;
	while (ft_isdigit(*str))
	{
		str++;
		len++;
	}
	if (len > 3)
		return (1);
	while (!ft_isdigit(*str))
		str++;
	len = 0;
	while (ft_isdigit(*str))
	{
		len++;
		str++;
	}
	if (len > 3)
		return (1);
	return (0);
}

int		ft_get_num(char *str)
{
	int	k;

	if (*str == '+')
		str++;
	if (!ft_isdigit(str[0]))
		return (-1);
	if (str[0] == '0' && str[1] == ' ')
		return (0);
	k = 0;
	while (str[k] == '0')
		k++;
	if (ft_isdigit(str[k]) == 0)
		return (0);
	int num = ft_atoi(str + k);
	str += k;
	k = 0;
	while (ft_isdigit(str[k]))
		k++;
	if (k > 3 || 255 < num)
		return (-1);
	return (num);
}

char 	*ft_skip_separator(char *str)
{
	if (*str == '+')
		str++;
	while (ft_isdigit(*str))
		str++;
	if (*str != ' ' && *str != ',')
		return (NULL);
	while (*str == ' ')
		str++;
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
