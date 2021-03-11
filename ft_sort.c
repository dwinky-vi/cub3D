/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 21:43:42 by dwinky            #+#    #+#             */
/*   Updated: 2021/03/12 00:03:16 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub3d.h"

static void	ft_swap_sprite(t_sprite *sprite1, t_sprite *sprite2)
{
	t_sprite tmp;

	tmp = *sprite1;
	*sprite1 = *sprite2;
	*sprite2 = tmp;
}

void		ft_quick_sort(t_sprite *sprite, int first, int last)
{
	int		left;
	int		right;
	double	center;

	if (first > last)
		return ;
	left = first;
	right = last;
	center = sprite[(first + last) / 2].distance;
	while (left <= right)
	{
		while (sprite[left].distance > center)
			left++;
		while (center > sprite[right].distance)
			right--;
		if (left <= right)
		{
			if (sprite[left].distance < sprite[right].distance)
				ft_swap_sprite(sprite + left, sprite + right);
			left++;
			right--;
		}
	}
	if (right > 0)
		ft_quick_sort(sprite, first, right);
	if (left < last)
		ft_quick_sort(sprite, left, last);
}

void		ft_insert_sort(t_sprite *sprite, int size)
{
	int		k;
	int		j;

	k = 0;
	while (k < size)
	{
		j = k;
		while (j > 0 && sprite[j - 1].distance < sprite[j].distance)
		{
			ft_swap_sprite(sprite + j - 1, sprite + j);
			j--;
		}
		k++;
	}
}
