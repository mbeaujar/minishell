/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 00:12:30 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/04/13 15:39:21 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env *newlstenv(char *env)
{
	t_env *new;
	char *name;
	char *value;

	if (!(new = malloc(sizeof(t_env) * 1)))
		return (NULL);
	new->name = env;
	new->value = env;
	new->next = NULL;
	return (new);
}

void addlstenv(t_env **head, char *env)
{
	t_env *tmp;

	if (!*head)
	{
		*head = newlstenv(env);
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = newlstenv(env);
}

void printlstenv(t_env *head)
{
	while (head)
	{
		//printf("%s\n", head->data);
		head = head->next;
	}
}

void freelstenv(t_env *head)
{
	t_env *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}