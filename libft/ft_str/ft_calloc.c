/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 21:54:05 by beaujardm         #+#    #+#             */
/*   Updated: 2020/12/11 18:10:23 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void		*ft_calloc(size_t count, size_t size)
{
	char *s;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	if (!(s = malloc(count * size)))
		return (NULL);
	if (s)
		ft_bzero(s, (count * size));
	return ((void*)s);
}
