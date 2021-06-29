/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:43:04 by dwinky            #+#    #+#             */
/*   Updated: 2020/11/18 23:16:59 by vitaly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			k;
	unsigned char	ch;
	unsigned char	*str;

	str = (unsigned char *)s;
	ch = (unsigned char)c;
	k = 0;
	while (k != n)
	{
		if (*(str + k) == ch)
			return (str + k);
		k++;
	}
	return (NULL);
}
