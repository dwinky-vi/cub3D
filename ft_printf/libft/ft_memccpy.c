/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:41:59 by dwinky            #+#    #+#             */
/*   Updated: 2020/11/18 23:16:29 by vitaly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			k;
	size_t			f;
	unsigned char	u_ch;
	unsigned char	*src_str;
	unsigned char	*dst_str;

	f = 0;
	src_str = (unsigned char *)src;
	dst_str = (unsigned char *)dst;
	u_ch = (unsigned char)c;
	k = 0;
	while (k != n)
	{
		dst_str[k] = src_str[k];
		if (src_str[k] == u_ch)
		{
			f = 1;
			k++;
			break ;
		}
		k++;
	}
	if (f == 0)
		return (NULL);
	return (dst_str + k);
}
