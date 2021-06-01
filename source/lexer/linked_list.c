/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 19:21:58 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/01 20:09:28 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*newlstlexer(char *token, t_type key)
{
	t_lexer	*new;

	new = malloc(sizeof(t_lexer) * 1);
	if (!new)
		return (NULL);
	new->token = token;
	new->key = key;
	new->previous = NULL;
	new->next = NULL;
	return (new);
}

void	lstaddbacklexer(t_lexer **head, t_lexer *new)
{
	t_lexer	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->previous = tmp;
}

void	freelstlexer(t_lexer **begin)
{
	t_lexer	*tmp;
	t_lexer	*head;

	head = *begin;
	if (!begin || !*begin)
		return ;
	while (head->previous)
		head = head->previous;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->token);
		free(tmp);
	}
	*begin = NULL;
}

void	printlstlexer(t_lexer *head)
{
	if (!head)
		return ;
	while (head->previous)
		head = head->previous;
	while (head)
	{
		ft_putstr_fd("token : ", 0);
		ft_putstr_fd(head->token, 1);
		ft_putchar_fd('\t', 0);
		if (head->key == PIP)
			ft_putstr_fd("PIP", 1);
		if (head->key == COMAT)
			ft_putstr_fd("COMAT", 1);
		if (head->key == LEFT)
			ft_putstr_fd("LEFT", 1);
		if (head->key == RIGHT)
			ft_putstr_fd("RIGHT", 1);
		if (head->key == DEFAULT)
			ft_putstr_fd("DEFAULT", 1);
		if (head->key == PATH)
			ft_putstr_fd("PATH", 1);
		ft_putchar_fd('\n', 0);
		head = head->next;
	}
}

int	lstsizelexer(t_lexer *head)
{
	int	i;

	i = 0;
	if (!head)
		return (0);
	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}
