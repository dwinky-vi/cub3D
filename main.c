/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:54:32 by dwinky            #+#    #+#             */
/*   Updated: 2021/02/18 13:46:46 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"
// #include "minilibx_opengl_20191021/mlx.h"

/*
** a == 0
** s == 1
** d == 2
** w == 13
** esc = 53
*/

int		deal_key(int key, t_vars *vars)
{
	if (key == 53)
		// mlx_clear_window(vars->mlx_ptr, vars->win_ptr);
		mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
	ft_putnbr(key);
	ft_putchar(' ');
	// mlx_pixel_put(mlx_ptr, win_ptr, );
	return (-1);
}

typedef struct  s_data2
{
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data2;

void            my_mlx_pixel_put(t_data2 *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int		main(int argc, char **argv)
{
	(void)argc;
	void		*mlx_ptr;
	void		*win_ptr;
	int			fd;
	t_data		data;
	t_vars vars;
	char		*error;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_puterror("Error in fd"));
	data = ft_get_data(fd);
	if (data.error != NULL)
		return (ft_puterror(data.error));
	ft_print_config(data.config);
	ft_print_map(data.map);
	if ((error = ft_validator(&data)))
		return (ft_puterror(error));
	// ft_free_map(data.map);
	// ft_free_config(&(data.config));
	close(fd);
	
	vars.mlx_ptr = mlx_init();
	if (vars.mlx_ptr == NULL)
		return (ft_puterror("Error in mlx_init()"));
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, 1920, 1080, "planet");
	// int k = 0;
	// while ((data.map)[k])
	// {
	// 	int j = 0;
	// 	while ((data.map)[k][j])
	// 	{
	// 		if (data.map[k][j] == '1')
	// 		{
	// 			mlx_pixel_put(vars.mlx_ptr, vars.win_ptr, k, j, data.config.c_int);
	// 			// mlx_pixel_put(vars.mlx_ptr, vars.win_ptr, k, j + 1, data.config.c_int);
	// 			// mlx_pixel_put(vars.mlx_ptr, vars.win_ptr, k, j + 2, data.config.c_int);
	// 			// mlx_pixel_put(vars.mlx_ptr, vars.win_ptr, k, j + 3, data.config.c_int);
	// 		}
	// 		j++;
	// 	}
	// 	k++;
	// }
	// mlx_key_hook(vars.win_ptr, deal_key, &vars);
	// mlx_loop(vars.mlx_ptr);

	t_data2  img;
	img.img = mlx_new_image(vars.mlx_ptr, 1920, 1080);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    my_mlx_pixel_put(&img, 500, 500, 0x00FF0000);
    mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, img.img, 0, 1231);
    mlx_loop(vars.mlx_ptr);

	return (0);
}
