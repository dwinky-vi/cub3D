/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:54:26 by dwinky            #+#    #+#             */
/*   Updated: 2021/01/31 21:01:01 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUB3D_H
# define FT_CUB3D_H 

# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"

typedef	struct s_window
{
	int	size_x;
	int	size_y;
}				t_window;

typedef struct s_config
{
	t_window	r;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;
	char	*f_str;
	int		f_int;
	char	*c_str;
	int		c_int;
}				t_config;

typedef struct s_data
{
	t_config	config;
	char		**map;
	char		*error;
}				t_data;

int		ft_puterror(char *str);

void	ft_lstprint_ass_str(t_list **list);

void	ft_print_map(char **map);

void	ft_print_config(t_config config);

void	ft_free_map(char **map);

void	ft_free_config(t_config *conf);

t_data	ft_get_data(int fd);

t_list	*ft_make_list_map(int fd, char *line);

char	**ft_convert_lst_to_matrix(t_list **lst);

char    *ft_validator(t_data *data);
#endif
