/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 00:12:14 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/04/13 18:17:16 by mbeaujar         ###   ########.fr       */
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