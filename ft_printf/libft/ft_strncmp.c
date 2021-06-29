/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:52:41 by dwinky            #+#    #+#             */
/*   Updated: 2020/10/28 15:52:43 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t num)
{
	size_t k;

	k = 0;
	if (num == 0)
		return (0);
	while (k != num - 1 && s1[k] == s2[k] && s1[k] != '\0')
		k++;
	return ((unsigned char)s1[k] - (unsigned char)s2[k]);
}
