/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validator2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:29:49 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/18 03:41:27 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

int		ft_check_resolution(int *width, int *height, void *mlx_ptr)
{
	int	my_width;
	int	my_height;

	if (*width <= 0 || *height <= 0)
		return (1);
	mlx_get_screen_size(mlx_ptr, &my_width, &my_height);
	if (my_width < *width)
		*width = my_width;
	if (my_height < *height)
		*height = my_height;
	return (0);
}

int		ft_check_and_get_color(char *str, int *color)
{
	int	num1;
	int	num2;
	int	num3;

	num1 = ft_get_num(str);
	if (!(str = ft_skip_separator(str)))
		return (1);
	num2 = ft_get_num(str);
	if (!(str = ft_skip_separator(str)))
		return (1);
	num3 = ft_get_num(str);
	if (*str == '+')
		str++;
	while (ft_isdigit(*str))
		str++;
	while (*str == ' ')
		str++;
	if (*str != '\0')
		return (1);
	if (num1 < 0 || num2 < 0 || num3 < 0)
		return (1);
	*color = ft_get_color(num1, num2, num3);
	return (0);
}
