/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:49:45 by dwinky            #+#    #+#             */
/*   Updated: 2020/10/28 15:49:47 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	const char	*src_cpy;

	src_cpy = src;
	if (dst == NULL)
		return (0);
	if (size != 0)
	{
		while (size - 1 != 0 && *src != '\0')
		{
			size--;
			*dst++ = *src++;
		}
		*dst = '\0';
	}
	return (ft_strlen(src_cpy));
}
