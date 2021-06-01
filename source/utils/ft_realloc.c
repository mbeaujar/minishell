/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 16:17:11 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/01 20:05:24 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** realloue une chaine à la bonne taille
*/

char	*ft_realloc(char *str)
{
	char	*new;
	int		i;

	i = 0;
	while (str[i])
		i++;
	new = malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = 0;
	free(str);
	return (new);
}
