/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:46:28 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/11 22:28:21 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

void			my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->b_p_p / 8));
	*(unsigned int *)dst = color;
}

unsigned int	ft_mlx_get_color(t_texture *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->b_p_p / 8));
	return (*(unsigned int *)dst);
}

int				ft_init_img(void *mlx_ptr, t_img *img, t_config *config)
{
	img->img = mlx_new_image(mlx_ptr, config->width, config->height);
	img->addr = mlx_get_data_addr(img->img, &img->b_p_p, &img->line_len,
									&img->endian);
	if (img->addr == NULL)
		return (1);
	return (0);
}
