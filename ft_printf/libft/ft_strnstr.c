/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:53:05 by dwinky            #+#    #+#             */
/*   Updated: 2020/11/01 00:19:08 by vitaly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s, const char *find, size_t size)
{
	size_t	k;
	size_t	j;
	char	*ptr;

	if (find[0] == '\0')
		return ((char *)s);
	k = 0;
	ptr = (char *)s;
	while (k != size && *ptr != '\0')
	{
		j = 0;
		while (ptr[j] == find[j] && ptr[j] && k + j < size)
			j++;
		if (find[j] == '\0')
			return (ptr);
		ptr++;
		k++;
	}
	return (NULL);
}
