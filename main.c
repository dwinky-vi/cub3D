/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:54:32 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/15 21:53:12 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"
#include <stdio.h>

#define ERROR01 "Error\n01 Not valid file"
#define ERROR02 "Error\n02 Problem in mlx"
#define ERROR03 "Error\n03 Bad textures"

int			ft_get_textures(void *mlx, t_texture *tex, t_config *config)
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

int			ft_check_file_cub(char *str)
{
	int k;
	
	k = 0;
	while (str[k])
	{
		if (str[k] == '.' && str[k + 1] == 'c' && str[k + 2] == 'u' &&
			str[k + 3] == 'b' && str[k + 4] == '\0')
			return (open(str, O_RDONLY));
		k++;
	}
	return (-1);

}
int			main(int argc, char **argv)
{
	int		fd;
	t_vars	vars;

	fd = ft_check_file_cub(argv[1]);
	if (fd == -1)
		return (ft_puterror(ERROR01));
	vars = ft_parse_data(fd);
	if (vars.data.error != NULL)
		return (ft_puterror(vars.data.error));
	vars.data.error = ft_validator(&vars.data, vars.mlx_ptr);
	if (vars.data.error != NULL)
		return (ft_puterror(vars.data.error));
	close(fd);
	vars.mlx_ptr = mlx_init();
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, vars.data.config.width, \
					vars.data.config.height, "CUB3D");
	if (vars.win_ptr == NULL)
		return (ft_puterror(ERROR02));
	if (ft_get_textures(vars.mlx_ptr, vars.texture, &vars.data.config))
		return (ft_puterror(ERROR03));
	ft_set_hooks(&vars);
	mlx_loop_hook(vars.mlx_ptr, ft_raycast, &vars);
	mlx_loop(vars.mlx_ptr);
	return (0);
}
