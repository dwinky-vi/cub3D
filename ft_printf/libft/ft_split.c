/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:47:29 by dwinky            #+#    #+#             */
/*   Updated: 2020/10/28 15:59:38 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlen_to_delimiter(char const *str, char delimiter)
{
	size_t	k;

	k = 0;
	while (str[k] != '\0' && str[k] != delimiter)
		k++;
	return (k);
}

static size_t	ft_count_words(char const *str, char ch)
{
	size_t	count_words;
	size_t	k;

	k = 0;
	count_words = 0;
	while (str[k] != '\0')
	{
		if (str[k] != ch)
		{
			count_words++;
			while (str[k] != ch && str[k] != '\0')
				k++;
		}
		else
			k++;
	}
	return (count_words);
}

static char		**ft_fill_array_of_words(char **array_of_words,
										size_t count_words,
										char const *s,
										char c)
{
	size_t	k;
	size_t	j;
	size_t	word_size;

	k = 0;
	while (k != count_words)
	{
		while (*s == c)
			s++;
		word_size = ft_strlen_to_delimiter(s, c);
		array_of_words[k] = (char *)ft_calloc((word_size + 1), sizeof(char));
		if (array_of_words[k] == NULL)
		{
			while (--k != 0)
				free(array_of_words[k]);
			free(array_of_words[0]);
			free(array_of_words);
			return (NULL);
		}
		j = 0;
		while (word_size-- != 0)
			*(array_of_words[k] + j++) = *s++;
		k++;
	}
	return (array_of_words);
}

char			**ft_split(char const *s, char c)
{
	char		**array_of_words;
	size_t		count_words;

	if (s == NULL)
		return (NULL);
	count_words = ft_count_words(s, c);
	array_of_words = (char **)ft_calloc(count_words + 1, sizeof(char *));
	if (array_of_words == NULL)
		return (NULL);
	array_of_words[count_words] = NULL;
	return (ft_fill_array_of_words(array_of_words, count_words, s, c));
}
