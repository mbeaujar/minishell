/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 19:36:27 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/01 17:25:00 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*normi_empty(void)
{
	char	*tab;

	tab = malloc(sizeof(char) * 1);
	if (!tab)
		return (NULL);
	tab[0] = '\0';
	return (tab);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	s_len;
	char			*tab;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len < start)
		return (normi_empty());
	tab = malloc(sizeof(char) * (len + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < len)
	{
		tab[i] = s[start];
		i++;
		start++;
	}
	tab[i] = '\0';
	return (tab);
}
