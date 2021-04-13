/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 19:00:45 by beaujardm         #+#    #+#             */
/*   Updated: 2020/12/11 18:10:23 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	b;
	size_t	l;

	i = 0;
	b = ft_strlen((char *)big);
	l = ft_strlen((char *)little);
	if (l == 0)
		return ((char *)big);
	if (len <= 0 || b < l)
		return (NULL);
	while (big[i])
	{
		j = 0;
		while (i + j < len && i + j < b && j < l && big[i + j] == little[j])
			j++;
		if (j == len || j == l)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
