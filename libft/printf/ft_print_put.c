/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_put.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 15:19:42 by mbeaujar          #+#    #+#             */
/*   Updated: 2020/12/11 19:09:17 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int		ft_strlen_printf(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_printstr(char *str, int max)
{
	int i;

	i = 0;
	while (str[i] && i < max)
		ft_printchar(str[i++]);
	return (i);
}

int		ft_printhex(unsigned int nb, char value)
{
	char	s[8];
	int		i;
	int		print;

	i = 0;
	if (nb == 0)
		s[i++] = '0';
	while (nb)
	{
		if ((nb % 16) < 10)
			s[i] = (nb % 16) + '0';
		else
		{
			if (value == 'x')
				s[i] = (nb % 16) + 87;
			else
				s[i] = (nb % 16) + 55;
		}
		nb /= 16;
		i++;
	}
	print = i;
	while (--i >= 0)
		ft_printchar(s[i]);
	return (print);
}

int		ft_printaddr(unsigned long addr_l)
{
	char	aff[20];
	int		i;
	int		print;

	i = 0;
	if (addr_l == 0)
		aff[i++] = '0';
	while (addr_l)
	{
		if ((addr_l % 16) < 10)
			aff[i] = (addr_l % 16) + '0';
		else
			aff[i] = (addr_l % 16) + 87;
		addr_l /= 16;
		i++;
	}
	print = i;
	while (--i >= 0)
		ft_printchar(aff[i]);
	return (print);
}

void	ft_putnbr(unsigned int nbr)
{
	if (nbr >= 10)
	{
		ft_putnbr(nbr / 10);
		ft_putnbr(nbr % 10);
	}
	else
		ft_printchar(nbr + '0');
}
