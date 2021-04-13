/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 15:32:29 by mbeaujar          #+#    #+#             */
/*   Updated: 2020/12/11 18:49:37 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ft_print_hex_dot(unsigned int nbr, t_flags flags, char value)
{
	int print;

	print = 0;
	if (flags.dot >= 0)
		print += ft_print(flags.dot, ft_len_hex(nbr), '0');
	print += ft_printhex(nbr, value);
	return (print);
}

int	ft_print_hex_width(unsigned int nbr, t_flags flags, char value)
{
	int print;

	print = 0;
	if (flags.less == 1)
		print += ft_print_hex_dot(nbr, flags, value);
	if (flags.dot >= 0 && (flags.dot < ft_len_hex(nbr)))
		flags.dot = ft_len_hex(nbr);
	if (flags.dot >= 0)
		print += ft_print(flags.width, flags.dot, ' ');
	else
		print += ft_print(flags.width, ft_len_hex(nbr), flags.zero);
	if (flags.less == 0)
		print += ft_print_hex_dot(nbr, flags, value);
	return (print);
}

int	ft_print_hex(unsigned int nbr, t_flags flags, char value)
{
	int print;

	print = 0;
	if (flags.dot == 0 && nbr == 0)
		return (ft_print(flags.width, 0, ' '));
	print = ft_print_hex_width(nbr, flags, value);
	return (print);
}
