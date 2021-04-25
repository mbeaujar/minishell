/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaujardmael <beaujardmael@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 20:05:05 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/04/25 14:45:40 by beaujardmae      ###   ########.fr       */
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
