/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_address.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 16:22:28 by mbeaujar          #+#    #+#             */
/*   Updated: 2020/12/11 18:49:28 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ft_print_address_dot(unsigned long nbr, t_flags flags)
{
	int print;

	print = ft_printstr("0x", 2);
	if (flags.dot >= 0)
	{
		print += ft_print(flags.dot, ft_len_mem(nbr), '0');
		print += ft_printaddr(nbr);
	}
	else
		print += ft_printaddr(nbr);
	return (print);
}

int	ft_print_address_zero(t_flags flags)
{
	int print;

	print = 0;
	if (flags.less == 1)
		print += ft_printstr("0x", 2);
	print += ft_print(flags.width, 2, ' ');
	if (flags.less == 0)
		print += ft_printstr("0x", 2);
	return (print);
}

int	ft_print_address(unsigned long nbr, t_flags flags)
{
	int print;

	print = 0;
	if (flags.dot == 0 && nbr == 0)
		return (ft_print_address_zero(flags));
	if (flags.dot >= 0 && (flags.dot < ft_len_mem(nbr)))
		flags.dot = ft_len_mem(nbr);
	if (flags.less == 1)
		print += ft_print_address_dot(nbr, flags);
	if (flags.zero == '0' && flags.dot == -1)
		flags.dot = flags.width;
	print += ft_print(flags.width, ft_len_mem(nbr) + 2, ' ');
	if (flags.less == 0)
		print += ft_print_address_dot(nbr, flags);
	return (print);
}
