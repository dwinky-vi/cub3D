#ifndef T_STRUCTURES_H
# define T_STRUCTURES_H

typedef struct  	s_vars
{
        void    	*mlx_ptr;
        void    	*win_ptr;
}               	t_vars;

typedef struct		s_point
{
	int 			x;
	int				y;
}					t_point;

typedef	struct		s_window_size
{
					int	size_x;
					int	size_y;
}					t_window_size;

typedef struct		s_config
{
	t_window_size	r;
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

#endif