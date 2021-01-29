/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitaly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 21:19:16 by vitaly            #+#    #+#             */
/*   Updated: 2020/11/18 23:47:21 by vitaly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_size_nbr(int n)
{
	size_t			size;
	unsigned int	n_cpy;

	size = 1;
	if (n < 0)
	{
		n_cpy = (unsigned int)-n;
		size++;
	}
	n_cpy = (unsigned int)n;
	while (n_cpy > 9)
	{
		size++;
		n_cpy /= 10;
	}
	return (size);
}

static void		ft_itoa_help(unsigned int nbr, char *res)
{
	if (nbr > 9)
		ft_itoa_help(nbr / 10, res);
	while (*res != '\0')
		res++;
	*res = nbr % 10 + '0';
}

char			*ft_itoa(int n)
{
	char *res;

	res = (char *)ft_calloc(ft_size_nbr(n) + 1, sizeof(char));
	if (res != NULL && n < 0)
	{
		res[0] = '-';
		ft_itoa_help((unsigned int)(-n), res);
	}
	else if (res != NULL)
		ft_itoa_help((unsigned int)(n), res);
	return (res);
}
