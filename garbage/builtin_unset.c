/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaujardmael <beaujardmael@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 19:09:27 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/04/25 15:29:47 by beaujardmae      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void unset(t_var *var, char *path)
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
		to_delete = search_env(var->head, unset[i]);
		if (to_delete)
		{
			printf("delete : '%s'\n", to_delete->name);
			delete_env(var, to_delete);
		}
		i++;
	}
	i = 0;
	while (unset[i])
	{
		free(unset[i]);
		i++;
	}
	free(unset);
}
