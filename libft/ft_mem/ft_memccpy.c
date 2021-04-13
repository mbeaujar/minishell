/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 19:27:17 by beaujardm         #+#    #+#             */
/*   Updated: 2020/12/11 18:10:23 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*dst_c;
	unsigned char	*src_c;

	src_c = (unsigned char*)src;
	dst_c = (unsigned char*)dst;
	i = 0;
	while (i < n && src_c[i] != (unsigned char)c)
	{
		dst_c[i] = src_c[i];
		i++;
	}
	if (i == n)
		return (NULL);
	else
	{
		dst_c[i] = src_c[i];
		i++;
		return (&dst_c[i]);
	}
}
