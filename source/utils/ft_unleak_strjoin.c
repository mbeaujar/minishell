/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unleak_strjoin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:14:08 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/16 16:14:09 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unleak_strjoin(char **dst, char *src)
{
	char *tmp;

	if (!*dst)
	{
		*dst = ft_strdup(src);
		return ;
	}
	tmp = ft_strdup(*dst);
	free(*dst);
	*dst = ft_strjoin(tmp, src);
	free(tmp);
}
