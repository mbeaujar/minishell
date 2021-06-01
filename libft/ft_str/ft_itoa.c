/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 18:24:12 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/01 17:22:21 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	len(int n)
{
	unsigned int	nb;
	int				i;

	i = 0;
	if (n < 0)
	{
		nb = -n;
		i++;
	}
	else
		nb = n;
	while (nb)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

static unsigned int	value(int n)
{
	unsigned int	nb;

	if (n < 0)
		nb = -n;
	else
		nb = n;
	return (nb);
}

static char	*zero(void)
{
	char	*tab;

	tab = malloc(sizeof(char) * 2);
	if (!tab)
		return (NULL);
	tab[0] = '0';
	tab[1] = '\0';
	return (tab);
}

char	*ft_itoa(int n)
{
	unsigned int	nb;
	int				i;
	char			*tab;

	i = len(n);
	nb = value(n);
	if (n == 0)
	{
		tab = zero();
		return (tab);
	}
	tab = malloc(sizeof(char) * (i + 1));
	if (!tab)
		return (NULL);
	tab[i] = '\0';
	i--;
	while (nb)
	{
		tab[i] = (nb % 10) + 48;
		nb /= 10;
		i--;
	}
	if (n < 0)
		tab[i] = '-';
	return (tab);
}
