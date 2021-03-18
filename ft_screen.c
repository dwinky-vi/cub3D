/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 07:07:39 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/18 09:11:46 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"
#define ERROR00 "Error\n00 file is missing"
#define ERROR01 "Error\n01 Not valid file"

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

void	ft_make_screen(t_vars *vars, t_scrn *scrn, char *str)
{
	if (ft_strncmp(str, "--save", 6) == 0 && ft_strlen(str) == 6)
	{
		vars->f_save = TRUE;
		scrn->fd = open("screenshot.bmp", O_CREAT | O_RDWR | O_TRUNC, 0666);
		if (scrn->fd == -1)
		{
			ft_puterror("Error\nBad fn in screenshoot");
			exit(0);
		}
		vars->data.config.width = scrn->width;
		vars->data.config.height = scrn->height;
		ft_raycast(vars);
		ft_init_scrn(scrn);
		ft_write_bmp(scrn, vars->img.b_p_p);
		while (scrn->height > 0)
		{
			scrn->height--;
			write(scrn->fd, vars->img.addr + (scrn->height *
			vars->img.line_len), (scrn->width * (vars->img.b_p_p / 8)));
		}
		close(scrn->fd);
		exit(0);
	}
	ft_puterror("Error\nInvalid argv in screenshoot");
	exit(0);
}

void	ft_check_arg(int c, char *str, int *fd)
{
	if (c == 1 || 3 < c)
	{
		ft_puterror(ERROR00);
		exit(0);
	}
	*fd = ft_check_file_cub(str);
	if (*fd == -1)
	{
		ft_puterror(ERROR01);
		exit(0);
	}
}
