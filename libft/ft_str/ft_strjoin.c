/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 19:24:48 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/01 17:18:47 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tab;
	int		i;
	int		y;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	tab = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!tab)
		return (NULL);
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	y = 0;
	while (s2[y])
	{
		tab[i + y] = s2[y];
		y++;
	}
	tab[i + y] = '\0';
	return (tab);
}
