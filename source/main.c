/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 20:05:05 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/04/14 16:53:18 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// envp = toutes les variable d'environnement

int main(int argc, char **argv, char **envp)
{
	t_env *head;
	
	head = NULL;
	if (argc && argv)
	{
		head = fill_env(envp);
		prompt(head);
		freelstenv(head);
	}
	// head = NULL;
	// system("leaks minishell");
	return (0);
}