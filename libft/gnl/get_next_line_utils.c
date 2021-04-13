/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 15:33:11 by mbeaujar          #+#    #+#             */
/*   Updated: 2020/12/27 15:11:13 by beaujardm        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line.h"
#include <stdio.h>

size_t		ft_strlen_gnl(const char *s)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

/*
** check si le buffer contient un retour à la ligne
*/

int			is_endl(char *save)
{
	int i;

	i = 0;
	if (!save)
		return (0);
	while (save[i])
	{
		if (save[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void		*ft_memmove_gnl(void *dst, const void *src, size_t len)
{
	char *d;
	char *s;

	d = (char *)dst;
	s = (char *)src;
	if (dst == src)
		return (dst);
	if (s < d)
	{
		while (len--)
			*(d + len) = *(s + len);
		return (dst);
	}
	while (len--)
		*d++ = *s++;
	return (dst);
}

char		*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*tab;

	if (!s1 && !s2)
		return (NULL);
	if (!(tab = malloc(sizeof(char) * ((ft_strlen_gnl(s1) + ft_strlen_gnl(s2)) + 1))))
		return (NULL);
	if (!tab)
		return (0);
	ft_memmove_gnl(tab, s1, ft_strlen_gnl(s1));
	ft_memmove_gnl(tab + ft_strlen_gnl(s1), s2, ft_strlen_gnl(s2));
	tab[(ft_strlen_gnl(s1) + ft_strlen_gnl(s2))] = '\0';
	free(s1);
	return (tab);
}
