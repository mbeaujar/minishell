/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 15:18:58 by mbeaujar          #+#    #+#             */
/*   Updated: 2020/12/11 18:49:33 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ft_print_char(char c, t_flags flags)
{
	int print;

	print = 0;
	if (flags.less == 1)
		print += ft_printchar(c);
	print += ft_print(flags.width, 1, flags.zero);
	if (flags.less == 0)
		print += ft_printchar(c);
	return (print);
}

int	ft_print_no_type(char c, t_flags flags)
{
	int print;

	print = 0;
	if (c == '\0')
		return (0);
	if (flags.less == 1)
		print += ft_printchar(c);
	print += ft_print(flags.width, 0, flags.zero);
	if (flags.less == 0)
		print += ft_printchar(c);
	return (print);
}
