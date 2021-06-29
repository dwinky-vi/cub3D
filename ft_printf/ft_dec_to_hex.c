/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dec_to_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 17:26:02 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/21 21:49:52 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_reverse_str(char *str)
{
	size_t	k;
	size_t	len;
	char	buf;

	len = ft_strlen(str);
	k = 0;
	while (k < (len / 2))
	{
		buf = str[k];
		str[k] = str[len - k - 1];
		str[len - k - 1] = buf;
		k++;
	}
}

static void		to_hex(char *str, unsigned long long nbr)
{
	size_t	k;
	size_t	remainder;

	k = 0;
	while (nbr > 0)
	{
		remainder = nbr % 16;
		if (10 <= remainder && remainder <= 15)
			str[k] = 'a' + (remainder - 10);
		else
			str[k] = nbr % 16 + '0';
		nbr /= 16;
		k++;
	}
}

static int		len_of_num3(unsigned long long num)
{
	int k;

	k = 1;
	while (num > 9)
	{
		num /= 10;
		k++;
	}
	return (k);
}

char			*ft_dec_to_hex(unsigned long long nbr)
{
	char	*str;

	str = (char *)ft_calloc(1, len_of_num3(nbr) + 1);
	if (str == NULL)
		return (NULL);
	if (nbr == 0)
	{
		str[0] = '0';
		return (str);
	}
	to_hex(str, nbr);
	ft_reverse_str(str);
	return (str);
}
