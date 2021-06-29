/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:48:56 by dwinky            #+#    #+#             */
/*   Updated: 2020/10/28 15:48:58 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	k;
	char	*dup;

	dup = (char *)ft_calloc(ft_strlen(str) + 1, sizeof(char));
	k = 0;
	if (dup != NULL)
		while (str[k] != '\0')
		{
			dup[k] = str[k];
			k++;
		}
	return (dup);
}
