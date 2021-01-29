/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:44:38 by dwinky            #+#    #+#             */
/*   Updated: 2020/10/28 15:44:43 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t num)
{
	size_t			k;
	unsigned char	*s;
	unsigned char	u_ch;

	k = 0;
	u_ch = (unsigned char)c;
	s = (unsigned char *)b;
	while (k != num)
		*(s + k++) = u_ch;
	return (b);
}
