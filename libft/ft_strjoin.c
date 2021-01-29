/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:49:20 by dwinky            #+#    #+#             */
/*   Updated: 2020/10/28 15:49:22 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	k;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	k = 0;
	while (*s1 != '\0')
	{
		*str++ = *s1++;
		k++;
	}
	while (*s2 != '\0')
	{
		*str++ = *s2++;
		k++;
	}
	return (str - k);
}
