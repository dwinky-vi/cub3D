/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:52:30 by dwinky            #+#    #+#             */
/*   Updated: 2020/10/28 15:52:32 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*res;
	size_t	k;

	if (s == NULL)
		return (NULL);
	k = 0;
	res = (char *)ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	while (*s != '\0')
	{
		res[k] = (*f)(k, *s);
		s++;
		k++;
	}
	return (res);
}
