/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 18:25:31 by dwinky            #+#    #+#             */
/*   Updated: 2021/01/07 17:30:52 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putchar(int c)
{
	unsigned char u_ch;

	u_ch = (unsigned char)c;
	write(1, &(u_ch), 1);
	return (1);
}
