/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argv_strjoin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:14:03 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/16 16:14:04 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_argv_strjoin(char **dst, int count, ...)
{
	va_list	list;
	int		i;

	i = 0;
	va_start(list, count);
	while (i < count)
	{
		ft_unleak_strjoin(dst, va_arg(list, char *));
		i++;
	}
    va_end(list);
}
