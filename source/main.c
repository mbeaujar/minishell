/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 20:05:05 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/04/15 21:53:31 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// envp = toutes les variable d'environnement

void printerrno(void)
{
	char *error;

	error = strerror(errno);
	ft_putstr_fd(error, 0);
	ft_putchar_fd('\n', 0);
}

int main(int argc, char **argv, char **envp)
{
	t_var var;
	
	var.head = NULL;
	if (argc && argv)
	{
		var.head = fill_env(envp);
		printlstenv(var.head);
		/*t_env *test;
		test = search_env(var.head, "PWD");
		if (test)
			printf("TEST NAME : '%s' VALUE : '%s'\n", test->name, test->value);*/
		prompt(&var);
		freelstenv(var.head);
	}
	// head = NULL;
	// system("leaks minishell");
	return (0);
}