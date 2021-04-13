/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 18:32:53 by mbeaujar          #+#    #+#             */
/*   Updated: 2020/12/11 18:13:08 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_lstadd_back(t_list **alst, t_list *neww)
{
	t_list *cell;

	if (!*alst)
	{
		*alst = neww;
		return ;
	}
	cell = *alst;
	while (cell->next)
		cell = cell->next;
	cell->next = neww;
}
