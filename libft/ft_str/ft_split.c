/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaujardmael <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 22:23:49 by beaujardm         #+#    #+#             */
/*   Updated: 2021/01/08 14:05:02 by beaujardm        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int		count_word(char const *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != c &&
				(str[i + 1] == c || str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static int		len_word(char const *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

static char		**free_malloc(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static char		**fill(char const *str, char **tab, int len, char c)
{
	int i;
	int y;
	int word;

	i = -1;
	while (++i < len)
	{
		y = 0;
		while (str[y] == c)
			y++;
		if (str[y - 1] == c)
			str = str + y;
		word = len_word(str, c);
		if (!(tab[i] = malloc(sizeof(char) * (word + 1))))
			return (free_malloc(tab));
		y = 0;
		while (y < word)
			tab[i][y++] = *str++;
		tab[i][y] = '\0';
	}
	tab[i] = 0;
	return (tab);
}

char			**ft_split(char const *s, char c)
{
	int		len;
	char	**tab;

	if (!s)
		return (NULL);
	len = count_word(s, c);
	if (!(tab = malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	tab = fill(s, tab, len, c);
	return (tab);
}
