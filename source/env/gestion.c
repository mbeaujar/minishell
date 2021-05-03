/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 14:33:00 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/03 18:50:30 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_tab(char **envp)
{
	int i;

	i = 0;
	if (!*envp || envp == NULL || !envp)
		return ;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

char **new_table_env(t_env *head)
{
    char **envp;
	int i;
	int l;

	l = sizelstenv(head);
	if (!l)
		return (NULL);
	i = 0;
	if (!(envp = malloc(sizeof(char*) * (l + 1))))
		return (NULL);
	while (i < l && head)
	{
		if (!(envp[i] = ft_strjoin_env(head->name, head->value)))
		{
			free_tab(envp);
			return (NULL);
		}
		i++;
		head = head->next;
	}
	envp[i] = 0;
	return (envp);
}
