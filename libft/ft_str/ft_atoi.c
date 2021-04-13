/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:45:57 by beaujardm         #+#    #+#             */
/*   Updated: 2020/12/11 18:10:23 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	if (c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int			ft_atoi(const char *str)
{
	unsigned long long	num;
	int					check;
	int					i;
	int					neg;

	i = 0;
	check = 0;
	num = 0;
	neg = 1;
	while (whitespace(str[i]) == 1)
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		check++;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && check <= 1)
		num = (num * 10) + (str[i++] - '0');
	if (num > 9223372036854775807)
		return (neg < 0 ? 0 : -1);
	return (neg < 0 ? -num : num);
}
