#ifndef HEAD_STRUCTS_H
# define HEAD_STRUCTS_H

typedef struct	s_point
{
	int 		x;
	int			y;
}				t_point;

typedef	struct	s_window
{
	int			size_x;
	int			size_y;
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
	float		x;
	float		y;
	float		dir;
	float		start;
	float		end;
	double posX;
	double posY;  //x and y start position
  	double dirX;
	double dirY; //initial direction vector
  	double planeX;
	double planeY;
	double moveSpeed; //the constant value is in squares/second
    double rotSpeed;
}				t_person;

typedef struct  s_vars
{
    void    	*mlx_ptr;
    void    	*win_ptr;
	t_person	person;
	t_data		data;
	t_img		img;
	char		k_0;
	char		k_1;
	char		k_2;
	char		k_13;
}               t_vars;

#endif