/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validator1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:29:49 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/15 23:01:50 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

#define ERROR11 "Error\n11 Wrong window resolution (R)"
#define ERROR12 "Error\n12 Wrong floor color (F)"
#define ERROR13 "Error\n13 Wrong ceilling color (C)"
#define ERROR14 "Error\n14 Invalid symbols in map"
#define ERROR15 "Error\n15 Empty line in map"

int		ft_check_resolution(int *width, int *height, void *mlx_ptr)
{
	int	my_width;
	int	my_height;

	if (*width <= 0 || *height <= 0)
		return (1);
	mlx_get_screen_size(mlx_ptr, &my_width, &my_height);
	if (*width > my_width)
		*width = my_width;
	if (*height > my_height)
		*height = my_height;
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

int		ft_check_len_nums(char *str)
{
	int len;

	len = 0;
	//написать проверку на незначащие нули
	// проверить знаки + - в начале числа
	// проверить переполнение в разрешеним
	//
	//
	//






	if



	
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

int		ft_check_and_get_color(char *str, int *color)
{
	int	num1;
	int	num2;
	int	num3;

	if (ft_check_len_nums(str))
		return (1);
	num1 = ft_atoi(str);
	while (ft_isdigit(*str))
		str++;
	while (!ft_isdigit(*str))
		str++;
	num2 = ft_atoi(str);
	while (ft_isdigit(*str))
		str++;
	while (!ft_isdigit(*str))
		str++;
	num3 = ft_atoi(str);
	if (num1 < 0 || 255 < num1 || num2 < 0 || 255 < num2 || num3 < 0 || 255 < num3)
		return (1);
	*color = ft_get_color(num1, num2, num3);
	return (0);
}

char	*ft_validator(t_data *data, void *mlx_ptr)
{
	if (ft_check_resolution(&data->config.width, &data->config.height, mlx_ptr))
		return (ERROR11);
	if (ft_check_and_get_color(data->config.f_str, &(data->config.f_int)))
		return (ERROR12);
	if (ft_check_and_get_color(data->config.c_str, &(data->config.c_int)))
		return (ERROR13);
	if (ft_check_other_chars_map(data->map))
		return (ERROR14);
	if (ft_check_empty_line_map(data->map))
		return (ERROR15);
	return (NULL);
}

/*
** написать проход по всей карте. Проверить чтобы за \n не было очередного \n или space'а
** таким образом карта с пустой строкой будет не валидной и
** карта с пробелами на строке тоже будет невалидной
*/