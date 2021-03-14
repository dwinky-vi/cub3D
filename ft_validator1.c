/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validator1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:29:49 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/14 19:45:57 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

int		ft_check_resolution(int *width, int *height, void *mlx_ptr)
{
	// int	this_width;
	// int	this_height;

	// mlx_get_screen_size(mlx_ptr, &this_width, &this_height);
	// if (!(0 < *width && *width <= this_width))
	// 	*width = this_width;
	// if (!(0 < *height && *height <= this_height))
	// 	*height = this_height;
	return (0);
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

int		ft_check_and_get_color(char *str, int *color)
{
	int	num1;
	int	num2;
	int	num3;

	num1 = ft_atoi(str);
	if (!(0 <= num1 && num1 <= 255))
		return (1);
	while (ft_isdigit(*str))
		str++;
	while (!ft_isdigit(*str))
		str++;
	num2 = ft_atoi(str);
	if (!(0 <= num2 && num2 <= 255))
		return (1);
	while (ft_isdigit(*str))
		str++;
	while (!ft_isdigit(*str))
		str++;
	num3 = ft_atoi(str);
	if (!(0 <= num3 && num3 <= 255))
		return (1);
	*color = ft_get_color(num1, num2, num3);
	return (0);
}

char	*ft_validator(t_data *data, void *mlx_ptr)
{
	if (ft_check_resolution(&data->config.width, &data->config.height, mlx_ptr))
		return ("Error in window resolution (R)");
	if (ft_check_and_get_color(data->config.f_str, &(data->config.f_int)))
		return ("Error in floor color (F)");
	if (ft_check_and_get_color(data->config.c_str, &(data->config.c_int)))
		return ("Error in floor color (C)");
	if (ft_checking_map(data->map))
		return ("Error \nInvalid map");
	return (NULL);
}
