/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_gestion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 00:12:14 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/04/23 21:36:28 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env *fill_env(char **envp)
{
	int i;
	t_env *head;

	i = 0;
	head = NULL;
	while (envp[i])
	{
		addlstenv(&head, envp[i]);
		i++;
	}
	printlstenv(head);
	return (head);
}

void delete_env(t_var *var, t_env *to_delete)
{
	t_env *tmp;
	t_env *head;

	head = var->head;
	if (to_delete->name != NULL)
		free(to_delete->name);
	if (to_delete->value != NULL)
		free(to_delete->value);
	if (var->head == to_delete)
	{
		tmp = var->head;
		var->head = var->head->next;
		free(tmp);
		return;
	}
	while (head->next != NULL && head->next != to_delete)
		head = head->next;
	if (head->next == NULL)
		return;
	tmp = head->next;
	head->next = head->next->next;
	free(tmp);
}

int is_value(char *env)
{
	while (*env)
	{
		if (*env == '=')
			return (1);
		env++;
	}
	return (0);
}

t_env *newexport(char *env)
{
	t_env *new;

	if (!(new = malloc(sizeof(t_env) * 1)))
		return (NULL);
	new->name = env;
	new->value = NULL;
	new->export = 0;
	new->next = NULL;
	return(new);
}
