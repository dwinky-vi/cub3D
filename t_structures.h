#ifndef T_STRUCTURES_H
# define T_STRUCTURES_H

typedef struct		s_point
{
	int 			x;
	int				y;
}					t_point;

typedef	struct		s_window
{
					int	size_x;
					int	size_y;
}					t_window;

typedef struct		s_config
{
	t_window		r;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*s;
	char			*f_str;
	int				f_int;
	char			*c_str;
	int				c_int;
}					t_config;

typedef struct		s_data
{
	t_config		config;
	char			**map;
	char			*error;
}					t_data;

typedef struct  s_data2
{
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data2;

typedef struct  	s_vars
{
        void    	*mlx_ptr;
        void    	*win_ptr;
		t_point		person;
		t_data		data;
		t_data2		img;
}               	t_vars;
#endif