/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 21:46:16 by mbeaujar          #+#    #+#             */
/*   Updated: 2020/12/11 18:50:04 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

t_flags		ft_init_flags(void)
{
	t_flags flags;

	flags.zero = 32;
	flags.less = 0;
	flags.width = 0;
	flags.star = 0;
	flags.dot = -1;
	return (flags);
}

int			ft_is_type(const char c)
{
	if (c == 'c' || c == 's' || c == 'd' || c == 'i' || c == 'p')
		return (1);
	if (c == 'u' || c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

int			ft_is_digit(const char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int			ft_is_flags(const char c)
{
	if (c == '*' || c == ' ' || c == '.' || c == '-' || c == '0')
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void		ft_set_flags(const char *s, int *i, t_flags *flags, va_list args)
{
	*flags = ft_init_flags();
	while (s[*i] && ft_is_flags(s[*i]))
	{
		if (s[*i] == '-')
			ft_flags_less(flags);
		else if (s[*i] == '0' && flags->width == 0 && flags->less == 0)
			flags->zero = '0';
		else if (s[*i] == '.')
			ft_flags_dot(s, i, flags, args);
		else if (s[*i] == '*')
			ft_flags_width(flags, args);
		else if (ft_is_digit(s[*i]))
			ft_flags_digit(s, i, flags);
		if (!ft_is_type(s[*i]))
			(*i)++;
	}
}
