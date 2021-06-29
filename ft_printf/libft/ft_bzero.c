/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:00:31 by dwinky            #+#    #+#             */
/*   Updated: 2021/01/31 13:51:47 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t num)
{
	size_t			k;
	unsigned char	*str;

	str = (unsigned char *)s;
	k = 0;
	while (k != num)
		*(str + k++) = 0;
}
