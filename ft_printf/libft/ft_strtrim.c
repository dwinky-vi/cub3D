/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:53:37 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/16 20:30:57 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_set(char const *set, char ch)
{
	while (*set != '\0')
		if (*set++ == ch)
			return (1);
	return (0);
}

char		*ft_strtrim(char const *s, char const *set)
{
	size_t		k;
	char		*trimed;
	char const	*begin;
	char const	*end;

	if (s == NULL || set == NULL)
		return (NULL);
	k = 0;
	begin = s;
	while (ft_is_set(set, *(s + k++)) == 1)
		begin++;
	if (*begin == '\0')
		return ((char *)ft_calloc(1, sizeof(char)));
	k = ft_strlen(s);
	end = (s + k);
	while (ft_is_set(set, s[k-- - 1]) == 1)
		end--;
	trimed = (char *)ft_calloc((size_t)(end - begin) + 1, sizeof(char));
	k = 0;
	if (trimed != NULL)
		while (begin != end)
			*(trimed + k++) = *begin++;
	return (trimed);
}
