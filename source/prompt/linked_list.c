/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 19:04:55 by beaujardmae       #+#    #+#             */
/*   Updated: 2021/06/01 20:38:52 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_buff	*newlstbuffer(char *buff)
{
	t_buff	*new;

	new = malloc(sizeof(t_buff));
	if (!new)
		return (NULL);
	new->buff = buff;
	new->buff[0] = 0;
	new->len = 10;
	new->modified = 0;
	new->strlen = 0;
	new->previous = NULL;
	new->next = NULL;
	return (new);
}

void	lstaddfrontbuffer(t_buff **head, t_buff *new)
{
	t_buff	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->previous)
		tmp = tmp->previous;
	tmp->previous = new;
	new->next = tmp;
	*head = new;
}

void	printbuffer(char *str)
{
	if (!str)
		return ;
	while (*str)
	{
		if (*str > 0)
			ft_putchar_fd(*str, STDOUT_FILENO);
		str++;
	}
}

void	printlstbuffer(t_buff *head)
{
	int	i;

	i = 0;
	if (!head)
		return ;
	while (head->next)
		head = head->next;
	while (head)
	{
		ft_putstr_fd("\t", STDOUT_FILENO);
		ft_putnbr_fd(i, STDOUT_FILENO);
		if (head->modified == 1)
			ft_putchar_fd('*', STDOUT_FILENO);
		ft_putstr_fd("\t", STDOUT_FILENO);
		printbuffer(head->buff);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
		head = head->previous;
	}
}

void	freelstbuffer(t_buff **begin)
{
	t_buff	*tmp;
	t_buff	*head;

	head = *begin;
	if (!begin || !*begin)
		return ;
	while (head->previous)
		head = head->previous;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->buff);
		free(tmp);
	}
	*begin = NULL;
}
