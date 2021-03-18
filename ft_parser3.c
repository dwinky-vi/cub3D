/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:56:00 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/18 05:57:52 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

static int	ft_free_and_put_null(char **data)
{
	free(*data);
	*data = NULL;
	return (1);
}

int			ft_is_dublicate_id(t_config *config, char *line)
{
	if (line[0] == 'R' && config->width != 0)
	{
		config->width = -12;
		config->height = -13;
		return (1);
	}
	else if (line[0] == 'N' && line[1] == 'O' && config->no)
		return (ft_free_and_put_null(&config->no));
	else if (line[0] == 'S' && line[1] == 'O' && config->so)
		return (ft_free_and_put_null(&config->so));
	else if (line[0] == 'W' && line[1] == 'E' && config->we)
		return (ft_free_and_put_null(&config->we));
	else if (line[0] == 'E' && line[1] == 'A' && config->ea)
		return (ft_free_and_put_null(&config->ea));
	else if (line[0] == 'S' && config->s)
		return (ft_free_and_put_null(&config->s));
	else if (line[0] == 'F' && config->f_str)
		return (ft_free_and_put_null(&config->f_str));
	else if (line[0] == 'C' && config->c_str)
		return (ft_free_and_put_null(&config->c_str));
	return (0);
}

static char	*ft_check_w(char *str, long long *width)
{
	int	k;

	if (*str == '+')
		str++;
	if (!ft_isdigit(*str) || (*str == '0' && ft_isdigit(*str)))
		return (NULL);
	*width = atol(str);
	if (*width <= 0 || (long long)INT_MAX < *width)
		return (NULL);
	k = 0;
	while (ft_isdigit(str[k]))
		k++;
	if (k > 10)
		return (NULL);
	str += k;
	if (*str == ',')
		str++;
	while (*str == ' ')
		str++;
	if (*str == '+')
		str++;
	if (!ft_isdigit(*str) || (*str == '0' && ft_isdigit(*str)))
		return (NULL);
	return (str);
}

static char	*ft_check_h(char *str, long long *height)
{
	int k;

	if (str == NULL)
		return (NULL);
	*height = atol(str);
	if (*height <= 0 || (long long)INT_MAX < *height)
		return (NULL);
	k = 0;
	while (ft_isdigit(str[k]))
		k++;
	if (k > 10)
		return (NULL);
	str += k;
	return (str);
}

void		ft_get_w_h(char *str, int *w, int *h)
{
	char		*tmp;
	long long	height;
	long long	width;
	size_t		k;

	tmp = str;
	*w = -12;
	*h = -13;
	str = ft_check_w(str, &width);
	str = ft_check_h(str, &height);
	if (str == NULL)
	{
		free(tmp);
		return ;
	}
	while (*str == ' ')
		str++;
	if (*str != '\0')
	{
		free(tmp);
		return ;
	}
	free(tmp);
	*w = width;
	*h = height;
}
