/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 13:50:37 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/04 20:59:17 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printlstenv(t_env *head)
{
	while (head)
	{
		printf("name : '%s' value : '%s'\n", head->name, head->value);
		head = head->next;
	}
}

void	freelstenv(t_env **head)
{
	t_env	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp->name);
		free(tmp);
	}
	*head = NULL;
}

t_env	*search_env(t_env *head, char *env_name)
{
	if (!env_name)
		return (NULL);
	while (head)
	{
		if (!ft_strcmp(head->name, env_name))
			return (head);
		head = head->next;
	}
	return (NULL);
}

t_env	*fill_env(char **envp)
{
	int		i;
	t_env	*head;

	i = 0;
	head = NULL;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (!(addlstenv(&head, envp[i])))
		{
			freelstenv(&head);
			exit(5);
		}
		i++;
	}
	return (head);
}

void	delete_env(t_prompt *var, t_env *to_delete)
{
	t_env	*tmp;
	t_env	*head;

	head = var->env;
	if (to_delete->name != NULL)
		free(to_delete->name);
	if (to_delete->value != NULL)
		free(to_delete->value);
	if (var->env == to_delete)
	{
		tmp = var->env;
		var->env = var->env->next;
		free(tmp);
		return ;
	}
	while (head->next != NULL && head->next != to_delete)
		head = head->next;
	if (head->next == NULL)
		return ;
	tmp = head->next;
	head->next = head->next->next;
	free(tmp);
}
