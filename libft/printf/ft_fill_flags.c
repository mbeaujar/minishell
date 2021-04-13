/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 21:59:38 by mbeaujar          #+#    #+#             */
/*   Updated: 2020/12/11 18:49:20 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	ft_flags_less(t_flags *flags)
{
	flags->zero = ' ';
	flags->less = 1;
}

void	ft_flags_dot(const char *s, int *i, t_flags *flags, va_list args)
{
	(*i)++;
	if (s[*i] == '*')
	{
		flags->dot = va_arg(args, int);
		(*i)++;
	}
	else
	{
		flags->dot = 0;
		while (s[*i] >= '0' && s[*i] <= '9')
			flags->dot = flags->dot * 10 + (s[(*i)++] - '0');
	}
	(*i)--;
}

void	ft_flags_width(t_flags *flags, va_list args)
{
	flags->star = 1;
	flags->width = va_arg(args, int);
	if (flags->width < 0)
	{
		flags->less = 1;
		flags->width *= -1;
		flags->zero = ' ';
	}
}

void	ft_flags_digit(const char *s, int *i, t_flags *flags)
{
	if (flags->star == 1)
		flags->width = 0;
	while (s[*i] >= '0' && s[*i] <= '9')
		flags->width = flags->width * 10 + (s[(*i)++] - '0');
	(*i)--;
}
