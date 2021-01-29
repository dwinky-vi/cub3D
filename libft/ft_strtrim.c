/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:53:37 by dwinky            #+#    #+#             */
/*   Updated: 2020/11/18 23:46:02 by vitaly           ###   ########.fr       */
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

char		*ft_strtrim(char const *s1, char const *set)
{
	size_t		k;
	char		*trimed;
	char const	*begin;
	char const	*end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	k = 0;
	begin = s1;
	while (ft_is_set(set, *(s1 + k++)) == 1)
		begin++;
	if (*begin == '\0')
		return ((char *)ft_calloc(1, sizeof(char)));
	k = ft_strlen(s1);
	end = (s1 + k);
	while (ft_is_set(set, s1[k-- - 1]) == 1)
		end--;
	trimed = (char *)ft_calloc((size_t)(end - begin) + 1, sizeof(char));
	k = 0;
	if (trimed != NULL)
		while (begin != end)
			*(trimed + k++) = *begin++;
	return (trimed);
}
