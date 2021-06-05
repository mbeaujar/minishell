/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 17:44:01 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/04 21:21:08 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*newlstenv(char *env)
{
	t_env	*new;
	char	*name;
	char	*value;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	name = return_env_name(env);
	value = return_env_value(env);
	if (!value || !name)
	{
		free(new);
		secure_free(value);
		secure_free(name);
		return (NULL);
	}
	new->name = name;
	new->value = value;
	new->index = -1;
	new->next = NULL;
	return (new);
}

int	addlstenvnull(t_env **head, char *env)
{
	if (is_value(env))
	{
		*head = newlstenv(env);
		if (!*head)
			return (0);
	}
	else
	{
		*head = newlstenvnull(env);
		if (!*head)
			return (0);
	}
	return (1);
}

int	addlstenv(t_env **head, char *env)
{
	t_env	*tmp;

	if (!*head)
		return (addlstenvnull(head, env));
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	if (env && is_value(env))
	{
		tmp->next = newlstenv(env);
		if (!tmp->next)
			return (0);
	}
	else
	{
		tmp->next = newlstenvnull(env);
		if (!tmp->next)
			return (0);
	}
	return (1);
}

t_env	*newlstenvnull(char *env)
{
	t_env	*new;

	new = malloc(sizeof(t_env) * 1);
	if (!new)
		return (NULL);
	new->name = ft_strdup(env);
	new->value = NULL;
	new->index = -1;
	new->next = NULL;
	return (new);
}

int	sizelstenv(t_env *head)
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
