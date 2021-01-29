/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:39:53 by dwinky            #+#    #+#             */
/*   Updated: 2020/10/28 16:04:25 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t number, size_t size)
{
	unsigned char	*point;
	size_t			k;
	size_t			range;

	range = number * size;
	k = 0;
	point = (unsigned char *)malloc(range);
	if (point != NULL)
		while (k != range)
			*(point + k++) = '\0';
	return (point);
}
