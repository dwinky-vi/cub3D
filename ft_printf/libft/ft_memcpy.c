/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:43:24 by dwinky            #+#    #+#             */
/*   Updated: 2020/10/28 15:44:08 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t num)
{
	size_t				k;
	unsigned char		*dst_str;
	unsigned char const	*src_str;

	if (dst == NULL && src == NULL)
		return (NULL);
	dst_str = (unsigned char *)dst;
	src_str = (unsigned char const *)src;
	k = 0;
	while (k++ != num)
		*dst_str++ = *src_str++;
	return (dst);
}
