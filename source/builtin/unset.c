/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 14:28:35 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/07 22:15:34 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void unset(t_prompt *var, char *path)
{
	char **unset;
	int i;
	t_env *to_delete;

	i = 0;
	while (path[i] && path[i] != ' ')
		i++;
	unset = ft_split(path + i, ' ');
	i = 0;
	while (unset[i])
	{
		to_delete = search_env(var->env, unset[i]);
		if (to_delete)
		{
			printf("delete : '%s'\n", to_delete->name);
			delete_env(var, to_delete);
		}
		i++;
	}
    free_tab(unset);
} */

void unset(t_prompt *var, char **unset)
{
	int i;
	t_env *to_delete;

	i = 0;
	while (unset[i])
	{
		to_delete = search_env(var->env, unset[i]);
		if (to_delete)
		{
			printf("delete : '%s'\n", to_delete->name);
			delete_env(var, to_delete);
		}
		i++;
	}
	var->returned = 0;
}