/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:54:32 by dwinky            #+#    #+#             */
/*   Updated: 2021/02/18 21:26:28 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static int	mouse_press_hook(int key, void *vars)
{
	ft_putchar(key);
	ft_putchar('1');
	return (0);
}

static int	motion_hook(int key, void *vars)
{
	ft_putnbr(key);
	ft_putchar('2');
	return (0);
}

static int	expose_hook(int key, void *vars)
{
	ft_putnbr(key);
	ft_putchar('\n');
	return (0);
}

static int	exit_hook(int key, void *vars)
{
	ft_putstr("Exit");
	exit(0);
}

int		key_press_hook(int key, t_vars *vars)
{
	if (key == 53)
		exit(0);
	//move forward if no wall in front of you
	if (key == 13)
	{
		ft_putstr("13\n");
		if(vars->data.map[(int)(vars->person.posX + vars->person.dirX * vars->person.moveSpeed)][(int)vars->person.posY] == FALSE)
			vars->person.posX += vars->person.dirX * vars->person.moveSpeed;
		if(vars->data.map[(int)(vars->person.posX)][(int)(vars->person.posY + vars->person.dirY * vars->person.moveSpeed)] == FALSE)
			vars->person.posY += vars->person.dirY * vars->person.moveSpeed;
	}
	//move backwards if no wall behind you
	if (key == 1)
	{
		ft_putstr("1\n");
		if (vars->data.map[(int)(vars->person.posX - vars->person.dirX * vars->person.moveSpeed)][(int)vars->person.posY] == FALSE)
			vars->person.posX -= vars->person.dirX * vars->person.moveSpeed;
      	if (vars->data.map[(int)vars->person.posX][(int)(vars->person.posY - vars->person.dirY * vars->person.moveSpeed)] == FALSE)
			vars->person.posY -= vars->person.dirY * vars->person.moveSpeed;
	}
	//rotate to the left
	if (key == 0)
	{
		ft_putstr("0\n");
		//both camera direction and camera plane must be rotated
      	double oldDirX = vars->person.dirX;
      	vars->person.dirX = vars->person.dirX * cos(vars->person.rotSpeed) - vars->person.dirY * sin(vars->person.rotSpeed);
      	vars->person.dirY = oldDirX * sin(vars->person.rotSpeed) + vars->person.dirY * cos(vars->person.rotSpeed);
      	double oldPlaneX = vars->person.planeX;
      	vars->person.planeX = vars->person.planeX * cos(vars->person.rotSpeed) - vars->person.planeY * sin(vars->person.rotSpeed);
      	vars->person.planeY = oldPlaneX * sin(vars->person.rotSpeed) + vars->person.planeY * cos(vars->person.rotSpeed);
	}
	//rotate to the right
	if (key == 2)
	{
		ft_putstr("2\n");
		//both camera direction and camera plane must be rotated
    	double oldDirX = vars->person.dirX;
    	vars->person.dirX = vars->person.dirX * cos(-vars->person.rotSpeed) - vars->person.dirY * sin(-vars->person.rotSpeed);
    	vars->person.dirY = oldDirX * sin(-vars->person.rotSpeed) + vars->person.dirY * cos(-vars->person.rotSpeed);
    	double oldPlaneX = vars->person.planeX;
    	vars->person.planeX = vars->person.planeX * cos(-vars->person.rotSpeed) - vars->person.planeY * sin(-vars->person.rotSpeed);
    	vars->person.planeY = oldPlaneX * sin(-vars->person.rotSpeed) + vars->person.planeY * cos(-vars->person.rotSpeed);
	}
	return (0);
}

void	 set_hooks(t_vars *vars)
{
	vars->k_0 = FALSE;
	vars->k_1 = FALSE;
	vars->k_2 = FALSE;
	vars->k_13 = FALSE;
	// mlx_do_key_autorepeatoff(vars->mlx_ptr);
	mlx_hook(vars->win_ptr, 2, 0, key_press_hook, vars);
	// mlx_hook(vars->win_ptr, 3, 0, key_release_hook, vars);
	// mlx_hook(vars->win_ptr, 4, 0, mouse_press_hook, vars);
	// mlx_hook(vars->win_ptr, 5, 0, mouse_release_hook, v);
	// mlx_hook(vars->win_ptr, 6, 0, motion_hook, vars);
	// mlx_hook(vars->win_ptr, 12, 0, expose_hook, vars);
	mlx_hook(vars->win_ptr, 17, 0, exit_hook, vars);
}

static int		ft_puterror(char *str)
{
	ft_putendl_fd(str, 1);
	return (-1);
}

void            my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int		main(int argc, char **argv)
{
	(void)argc;
	int			fd;
	t_vars 		vars;
	char		*error;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_puterror("Error in fd"));
	vars = ft_parse_data(fd);
	if (vars.data.error != NULL)
		return (ft_puterror(vars.data.error));
	// ft_print_config(vars.data.config);
	// ft_print_map(vars.data.map);
	if ((error = ft_validator(&vars.data)))
		return (ft_puterror(error));
	close(fd);
	vars.mlx_ptr = mlx_init();
	if (vars.mlx_ptr == NULL)
		return (ft_puterror("Error in mlx_init()"));
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, vars.data.config.r.size_x, vars.data.config.r.size_y, "planet");
/**********************************************/
	double posX = 7, posY = 7;  //x and y start position
  	double dirX = -1, dirY = 0; //initial direction vector
  	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
  	double time = 0; //time of current frame
  	double oldTime = 0; //time of previous frame

  	// screen(vars.data.config.r.size_x, vars.data.config.r.size_y, 0, "Raycaster");
	int w = 10;
	for(int x = 0; x < w; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		//mapX и mapY представляют текущий квадрат карты, в котором находится луч
		int mapX = (int)posX;
		int mapY = (int)posY;

		//sideDistX и sideDistY изначально являются расстоянием, которое луч должен преодолеть от начального положения до первой стороны x и первой стороны y
		//длина луча от текущего положения до следующей стороны x или y
		double sideDistX;
		double sideDistY;

		//deltaDistX и deltaDistY - это расстояние, которое луч должен пройти, чтобы перейти от 1 стороны x к следующей стороне x или от 1 y-стороны к следующей стороне y
		double deltaDistX = ft_abs(1 / rayDirX);
		double deltaDistY = ft_abs(1 / rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (vars.data.map[mapX][mapY] > 0)
				hit = 1;
		}

		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (side == 0)
			perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

		int h = 10;
		//Calculate height of line to draw on screen
		int lineHeight = (int)(h / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if (drawEnd >= h)
			drawEnd = h - 1;

		//choose wall color
		int color;
		switch(vars.data.map[mapX][mapY])
		{
			case 1:  color = 0xFF0000;    break; //red
			case 2:  color = 0x008000;  break; //green
			case 3:  color = 0x0000FF;   break; //blue
			case 4:  color = 0xFFFFFF;  break; //white
			default: color = 0xFFFF00; break; //yellow
		}

		//give x and y sides different brightness
		if (side == 1)
			color = color / 2;

		//draw the pixels of the stripe as a vertical line
		// verLine(x, drawStart, drawEnd, color);
		my_mlx_pixel_put(&vars.img, drawEnd, drawStart, color);
	}
	//timing for input and FPS counter
	oldTime = time;
	time = 10;
	double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
	// print(1.0 / frameTime); //FPS counter
	// redraw();
	// cls();

	//speed modifiers
	double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
	double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
	// readKeys();
	/*
	posX и posY представляют вектор положения игрока, dirX и dirY представляют направление игрока, а planeX и planeY - плоскость камеры игрока
	*/
	vars.person.posX = posX;
	vars.person.posY = posY;
	vars.person.planeX = planeX;
	vars.person.planeY = planeY;
	vars.person.dirX = dirX;
	vars.person.dirY = dirY;
	vars.person.moveSpeed = moveSpeed;
	vars.person.rotSpeed = rotSpeed;
	vars.img.img = mlx_new_image(vars.mlx_ptr, vars.data.config.r.size_x, vars.data.config.r.size_y);
    vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);
	set_hooks(&vars);
	mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.img.img, 0, 0);
  /**********************************************/
	// mlx_loop_hook(vars.mlx_ptr, ft_func, &vars);
    mlx_loop(vars.mlx_ptr);
	return (0);
}
