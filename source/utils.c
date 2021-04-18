/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 16:55:29 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/04/18 16:45:38 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int search_where(char *s, char *search)
{
	size_t i;
	size_t j;
	size_t l;

	i = 0;
	l = ft_strlen(search);
	while (s[i])
	{
		j = 0;
		while (s[i + j]  == search[j] && s[i + j] && search[j])
			j++;
		if (j == l)
			return (i);
		i++;
	}
	return (-1);
}

char *search_and_replace(char *s, char *search, char *replace, int leak)
{
	char *str;
	int i;
	int limit;
	int len;

	if ((limit = search_where(s, search)) == -1)
		return (NULL);
	len = ((int)ft_strlen(s) - (int)ft_strlen(search)) + (int)ft_strlen(replace);
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (s[i] && i < limit)
	{
		str[i] = s[i];
		i++;
	}
	limit = i + (int)ft_strlen(search);
	while (*replace)
	{
		str[i] = *replace++;
		i++;
	}
	while (s[limit])
	{
		str[i] = s[limit];
		limit++;
		i++;
	}
	str[i] = 0;
	if (leak)
		free(s);
	return (str);
}