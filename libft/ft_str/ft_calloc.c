/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 21:54:05 by beaujardm         #+#    #+#             */
/*   Updated: 2021/06/05 13:04:22 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*s;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	s = malloc(count * size);
	if (!s)
		return (NULL);
	if (s)
		ft_bzero(s, (count * size));
	return ((void *)s);
}
