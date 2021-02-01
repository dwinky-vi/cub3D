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

typedef	struct s_size
{
	int	size_x;
	int	size_y;
}				t_size;

typedef struct s_config
{
	t_size	r;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;
	char	*f;
	char	*c;
}				t_config;

typedef struct s_data
{
	t_config	config;
	char		**map;
}				t_data;

void	ft_lstprint_ass_str(t_list **list);

void	ft_print_map(char **map);

void	ft_print_config(t_config config);

void	ft_free_map(char **map);

void	ft_free_config(t_config *conf);

t_data	ft_get_data(int fd);

t_list	*ft_make_list_map(int fd, char *line);

char	**ft_convert_lst_to_matrix(t_list **lst);

#endif
