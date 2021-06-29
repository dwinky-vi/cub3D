/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_u_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 21:37:53 by dwinky            #+#    #+#             */
/*   Updated: 2021/01/05 20:23:42 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_u_int(unsigned int n)
{
	char num;

	if (n <= 9)
	{
		num = n + (unsigned int)'0';
		write(1, &num, 1);
		return ;
	}
	ft_putnbr_u_int(n / 10);
	ft_putnbr_u_int(n % 10);
}
