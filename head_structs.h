/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:29:58 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/04 11:12:57 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_STRUCTS_H
# define HEAD_STRUCTS_H

typedef struct	s_point
{
	int 		x;
	int			y;
}				t_point;

typedef	struct	s_window
{
	int			width; // ширина
	int			height;// высота
}				t_window;

typedef struct	s_config
{
	t_window	r;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*s;
	char		*f_str;
	int			f_int;
	char		*c_str;
	int			c_int;
}				t_config;

typedef struct	s_data
{
	t_config	config;
	char		**map;
	char		*error;
}				t_data;

typedef struct  s_img
{
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_img;

typedef struct	s_person
{
	// координаты игрока
	double posX;
	double posY;
  	// направление персонажа, куда смотрю
	double dirX;
	double dirY;
	// угол обзора. плоскость которую видим
  	double planeX;
	double planeY;
	// скорость персонажа
	double moveSpeed;
	// скорость поворота камеры
    double rotSpeed;
}				t_person;

typedef struct  s_vars
{
    void    	*mlx_ptr;
    void    	*win_ptr;
	t_person	person;
	t_data		data;
	t_img		img;
	char		k_13;
	char		k_1;
	char		k_0;
	char		k_2;
	char		k_123;
	char		k_124;
	char		k_257;
}               t_vars;

#endif