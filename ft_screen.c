/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 07:07:39 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/18 08:18:04 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

void	ft_init_scrn(t_scrn *scrn)
{
	scrn->ppd_40 = 40;
	scrn->ppd_54 = 54;
	scrn->plane_1 = 1;
	scrn->sign_z = 0;
	scrn->u_z = 0;
}

void	ft_write_bmp(t_scrn *scrn, int bpp)
{
	scrn->size = scrn->width * scrn->height * 4 + 54;
	write(scrn->fd, "BM", 2);
	write(scrn->fd, &scrn->size, 4);
	write(scrn->fd, &scrn->u_z, 2);
	write(scrn->fd, &scrn->u_z, 2);
	write(scrn->fd, &scrn->ppd_54, 4);
	write(scrn->fd, &scrn->ppd_40, 4);
	write(scrn->fd, &scrn->width, 4);
	write(scrn->fd, &scrn->height, 4);
	write(scrn->fd, &scrn->plane_1, 2);
	write(scrn->fd, &bpp, 2);
	write(scrn->fd, &scrn->u_z, 4);
	write(scrn->fd, &scrn->u_z, 4);
	write(scrn->fd, &scrn->sign_z, 4);
	write(scrn->fd, &scrn->sign_z, 4);
	write(scrn->fd, &scrn->u_z, 4);
	write(scrn->fd, &scrn->u_z, 4);
}