/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:54:20 by dwinky            #+#    #+#             */
/*   Updated: 2020/10/28 15:54:21 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	k;
	size_t	j;
	char	*sub_str;

	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) <= start)
		return ((char *)ft_calloc(1, sizeof(char)));
	sub_str = (char *)ft_calloc((len + 1), sizeof(char));
	if (sub_str == NULL)
		return (NULL);
	k = start;
	j = 0;
	while (k != start + len && s[j] != '\0')
	{
		*sub_str++ = s[k];
		k++;
	}
	return (sub_str - len);
}
