/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:53:15 by dwinky            #+#    #+#             */
/*   Updated: 2020/10/28 15:53:17 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t		k;
	char		ch;
	const char	*p_ch;

	p_ch = NULL;
	ch = (char)c;
	k = 0;
	while (*(str + k) != '\0')
	{
		if (*(str + k) == ch)
			p_ch = str + k;
		k++;
	}
	if (*(str + k) == ch)
		return ((char *)(str + k));
	return ((char *)p_ch);
}
