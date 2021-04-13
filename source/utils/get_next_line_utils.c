/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 15:33:11 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/04/10 20:11:46 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t		ft_strlen(const char *s)
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

void		*ft_memmove(void *dst, const void *src, size_t len)
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

char		*ft_strjoin(char *s1, char *s2)
{
	char	*tab;
	int		i;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	if (!(tab = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1))))
		return (NULL);
	if (!tab)
		return (0);
	ft_memmove(tab, s1, ft_strlen(s1));
	ft_memmove(tab + ft_strlen(s1), s2, ft_strlen(s2));
	tab[(ft_strlen(s1) + ft_strlen(s2))] = '\0';
	free(s1);
	return (tab);
}
