/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 20:05:05 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/04/21 18:25:47 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// envp = toutes les variable d'environnement



int main(int argc, char **argv, char **envp)
{
	t_var var;
	
	var.head = NULL;
	if (argc && argv)
	{
		var.head = fill_env(envp);
		printlstenv(var.head);
		prompt(&var, envp);
		freelstenv(var.head);
	}
	return (0);
}