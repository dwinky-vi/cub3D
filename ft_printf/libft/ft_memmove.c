/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 19:13:35 by dwinky            #+#    #+#             */
/*   Updated: 2020/11/01 20:35:22 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t size)
{
	size_t			k;
	unsigned char	*dst_str;
	unsigned char	*src_str;

	if (src == NULL && dst == NULL)
		return (NULL);
	dst_str = (unsigned char *)dst;
	src_str = (unsigned char *)src;
	k = 0;
	if (dst_str > src_str)
	{
		src_str += size - 1;
		dst_str += size - 1;
		while (k++ != size)
			*dst_str-- = *src_str--;
	}
	else
		while (k++ != size)
			*dst_str++ = *src_str++;
	return (dst);
}
