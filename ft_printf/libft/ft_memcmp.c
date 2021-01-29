/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:43:15 by dwinky            #+#    #+#             */
/*   Updated: 2020/10/28 15:43:17 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				k;
	unsigned char const	*str1;
	unsigned char const	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	k = 0;
	if (n == 0)
		return (0);
	while (k < n - 1 && str1[k] == str2[k])
		k++;
	return (str1[k] - str2[k]);
}
