#include "head_cub3d.h"

static void	ft_swap_sprite(t_sprite *sprite1, t_sprite *sprite2)
{
	t_sprite tmp;

	tmp = *sprite1;
	*sprite1 = *sprite2;
	*sprite2 = tmp;
}

void		 ft_quick_sort(t_sprite *sprite, int first, int last)
{
	int		left;
	int		right;
	int		center;

	if (first <= last)
	{
		left = first;
		right = last;
		center = (first + last) / 2;
		while (left <= right)
		{
			while (sprite[left].distance > sprite[center].distance)
				left++;
			while (sprite[center].distance > sprite[right].distance)
				right--;
			if (left <= right)
			{
				if (sprite[left].distance < sprite[right].distance)
					ft_swap_sprite(sprite + left, sprite + right);
				left++;
				right--;
			}
		}
		if (0 < right)
			ft_quick_sort(sprite, first, right);
		if (left < last)
			ft_quick_sort(sprite, left, last);
	}
}

static void sortSprites(t_sprite *sprite, int count)
{
	int		k;
	int		j;

	k = 0;
	while (k < count)
	{
		j = 0;
		while (j < count)
		{
			if (sprite[k].distance > sprite[j].distance)
				ft_swap_sprite(sprite + j, sprite + k);
			j++;
		}
		k++;
	}
}

void	ft_insert_sort(t_sprite *sprite, int size)
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
