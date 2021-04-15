/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_linked_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 00:12:30 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/04/15 22:24:58 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env *newlstenv(char *env)
{
	t_env *new;
	char *name;
	char *value;

	if (!(new = malloc(sizeof(t_env) * 1)))
		return (NULL);
	if (!(name = return_env_name(env)))
	{
		free(new);
		return (NULL);
	}
	if (!(value = return_env_value(env)))
	{
		free(new);
		free(name);
		return (NULL);
	}
	new->name = name;
	new->value = value;
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
		printf("name : '%s' value : '%s'\n", head->name, head->value);
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

t_env *search_env(t_env *head, char *env_name)
{
	size_t len;
	
	len = ft_strlen(env_name) + 1;
	while (head)
	{
		if (!ft_strncmp(head->name, env_name, len))
			return (head);
		head = head->next;
	}
	return (NULL);
}