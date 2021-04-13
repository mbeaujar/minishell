/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 20:05:05 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/04/13 18:17:31 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


// envp = toutes les variable d'environnement

int main(int argc, char **argv, char **envp)
{
	t_env *head;
	char *name;
	char *value;
	//prompt();
	if (argc && argv)
	{
		head = fill_env(envp);
		freelstenv(head);
	}
	name = return_env_name(envp[0]);
	value = return_env_value(envp[0]);
	printf("name : %s\nvalue : %s\n", name, value);
	free(name);
	free(value);
	//prompt();
	// head = NULL;
	// system("leaks minishell");
	return (0);
}