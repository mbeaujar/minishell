/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 17:51:05 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/03 18:04:30 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_strjoin_env(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		y;

	if (!s1)
		return (NULL);
	i = 0;
	if (!(new = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 2))))
		return (NULL);
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
    new[i++] = '=';
	y = 0;
	while (s2 != NULL && s2[y])
	{
		new[i + y] = s2[y];
		y++;
	}
	new[i + y] = '\0';
	return (new);
}