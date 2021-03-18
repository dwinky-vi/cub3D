/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validator1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 02:57:47 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/18 03:34:53 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"
#define ERROR11 "Error\n11 Wrong window resolution (R)"
#define ERROR12 "Error\n12 Wrong floor color (F)"
#define ERROR13 "Error\n13 Wrong ceilling color (C)"
#define ERROR14 "Error\n14 Invalid symbols in map"
#define ERROR15 "Error\n15 Empty line in map"
#define ERROR16 "Error\n16 Map is not close "
#define ERROR17 "Error\n17 File NO is not xpm"
#define ERROR18 "Error\n18 File SO is not xpm"
#define ERROR19 "Error\n19 File WE is not xpm"
#define ERROR20 "Error\n20 File EA is not xpm"
#define ERROR21 "Error\n21 Zero not close "

/*
** 		_____main function_____
*/

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
	if (ft_check_edges(data->map))
		return (ERROR16);
	if (ft_check_xpm_file(data->config.no))
		return (ERROR17);
	if (ft_check_xpm_file(data->config.so))
		return (ERROR18);
	if (ft_check_xpm_file(data->config.we))
		return (ERROR19);
	if (ft_check_xpm_file(data->config.ea))
		return (ERROR20);
	if (ft_check_zero(data->map))
		return (ERROR21);
	return (NULL);
}
