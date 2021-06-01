/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:44:07 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/01 20:06:07 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_indexable(t_env *head)
{
	while (head)
	{
		if (head->index == -1)
			return (1);
		head = head->next;
	}
	return (0);
}

t_env	*search_index(t_env *head, int index)
{
	while (head)
	{
		if (head->index == index)
			return (head);
		head = head->next;
	}
	return (NULL);
}

int	max_index(t_env *head)
{
	int	index_max;

	index_max = head->index;
	while (head)
	{
		if (index_max < head->index)
			index_max = head->index;
		head = head->next;
	}
	return (index_max);
}

void	clear_index(t_env *head)
{
	while (head)
	{
		if (head->index != -2)
			head->index = -1;
		head = head->next;
	}
}

char	*return_export_name(char *env)
{
	int		i;
	char	*name;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
	{
		name[i] = env[i];
		i++;
	}
	name[i] = 0;
	return (name);
}
