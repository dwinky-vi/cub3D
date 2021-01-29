/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:55:40 by dwinky            #+#    #+#             */
/*   Updated: 2020/11/02 14:55:42 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	k;
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size <= dst_len)
		return (src_len + size);
	size -= dst_len;
	while (*dst != '\0')
		dst++;
	k = 0;
	size--;
	while (k < size && *src != '\0')
	{
		*dst++ = *src++;
		k++;
	}
	*dst = '\0';
	return (dst_len + src_len);
}
