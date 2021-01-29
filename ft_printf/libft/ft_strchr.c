/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:48:44 by dwinky            #+#    #+#             */
/*   Updated: 2020/10/28 15:48:47 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	size_t	k;

	k = 0;
	while (str[k] != '\0')
	{
		if (str[k] == c)
			return ((char *)(str + k));
		k++;
	}
	if (str[k] == c)
		return ((char *)(str + k));
	return (NULL);
}
