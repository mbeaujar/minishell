/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 17:44:01 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/07 18:16:16 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
	new->index = -1;
	new->next = NULL;
	return (new);
}

int addlstenvnull(t_env **head, char *env)
{
	if (is_value(env))
	{
		if (!(*head = newlstenv(env)))
			return (0);
	}
	else
	{
		if (!(*head = newlstenvnull(env)))
			return (0);
	}
	return (1);
}

int addlstenv(t_env **head, char *env)
{
	t_env *tmp;

	if (!*head)
		return (addlstenvnull(head, env));
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	if (is_value(env))
	{
		if (!(tmp->next = newlstenv(env)))
			return (0);
	}
	else
	{
		if (!(tmp->next = newlstenvnull(env)))
			return (0);
	}
	return (1);
}

t_env *newlstenvnull(char *env)
{
	t_env *new;

	if (!(new = malloc(sizeof(t_env) * 1)))
		return (NULL);
	new->name = env;
	new->value = NULL;
	new->index = -1;
	new->next = NULL;
	return(new);
}

int sizelstenv(t_env *head)
{
    int i;

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