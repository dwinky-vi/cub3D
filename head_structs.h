/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:29:58 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/06 21:50:00 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_STRUCTS_H
# define HEAD_STRUCTS_H

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_config
{
	int			width; // ширина
	int			height;// высота
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

typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct	s_texture
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			height;
	int			width;
}				t_texture;

typedef struct	s_person
{
	// координаты игрока
	double		pos_x;
	double		pos_y;
	// направление персонажа, куда смотрю
	double		dirX;
	double		dirY;
	// угол обзора. плоскость которую видим
	double		planeX;
	double		planeY;
	// скорость персонажа
	double		moveSpeed;
	// скорость поворота камеры
	double		rotSpeed;
}				t_person;

typedef struct	s_sprite
{
	double		x;
	double		y;
	double		distance;
}				t_sprite;

typedef struct	s_vars
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_person	person;
	t_data		data;
	t_img		img;
	t_texture	texture[5];
	int			count_sprites;
	char		k_13;
	char		k_1;
	char		k_0;
	char		k_2;
	char		k_123;
	char		k_124;
	char		k_257;
}				t_vars;

#endif
