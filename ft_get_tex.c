/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_tex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 03:26:45 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/18 03:39:26 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

int		ft_get_textures(void *mlx, t_texture *tex, t_config *config)
{
	tex[0].img = mlx_xpm_file_to_image(mlx, config->no, &tex[0].width,
										&tex[0].height);
	tex[0].addr = mlx_get_data_addr(tex[0].img, &tex[0].b_p_p,
									&tex[0].line_len, &tex[0].endian);
	tex[1].img = mlx_xpm_file_to_image(mlx, config->so, &tex[1].width,
										&tex[1].height);
	tex[1].addr = mlx_get_data_addr(tex[1].img, &tex[1].b_p_p,
									&tex[1].line_len, &tex[1].endian);
	tex[2].img = mlx_xpm_file_to_image(mlx, config->we, &tex[2].width,
										&tex[2].height);
	tex[2].addr = mlx_get_data_addr(tex[2].img, &tex[2].b_p_p,
									&tex[2].line_len, &tex[2].endian);
	tex[3].img = mlx_xpm_file_to_image(mlx, config->ea, &tex[3].width,
										&tex[3].height);
	tex[3].addr = mlx_get_data_addr(tex[3].img, &tex[3].b_p_p,
									&tex[3].line_len, &tex[3].endian);
	tex[4].img = mlx_xpm_file_to_image(mlx, config->s, &tex[4].width,
										&tex[4].height);
	tex[4].addr = mlx_get_data_addr(tex[4].img, &tex[4].b_p_p,
									&tex[4].line_len, &tex[4].endian);
	if (!tex[0].addr || !tex[1].addr || !tex[2].addr
			|| !tex[3].addr || !tex[4].addr)
		return (1);
	return (0);
}

int		ft_puterror(char *str)
{
	ft_putendl_fd(str, 1);
	return (-1);
}
