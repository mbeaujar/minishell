/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:55:34 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/01 20:37:59 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nbpipe(t_cmd *ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return (i);
	while (ptr && ptr->key == PIP)
	{
		ptr = ptr->next;
		i++;
	}
	return (i + 1);
}

int	command_not_found(t_prompt *prompt, char **args)
{
	if (prompt->isatty == 1)
		printf("bash: %s : command not found\n", args[0]);
	else
		printf("bash: line %d: %s: command not found\n", prompt->indice, args[0]);
	prompt->returned = 127;
	return (0);
}

void	which_command(t_prompt *prompt, t_cmd *ptr, char **args)
{
	if (ft_strcmp(args[0], "echo") == 0)
		echoo(prompt, args);
	else if (ft_strcmp(args[0], "cd") == 0)
		cd(prompt, args);
	else if (ft_strcmp(args[0], "export") == 0)
		export(prompt, args);
	else if (ft_strcmp(args[0], "env") == 0)
		env(prompt, args);
	else if (ft_strcmp(args[0], "exit") == 0)
		exitt(prompt, args);
	else if (ft_strcmp(args[0], "pwd") == 0)
		pwd(prompt, args);
	else if (ft_strcmp(args[0], "unset") == 0)
		unset(prompt, args);
	else
		unbuiltin(prompt, ptr, args);
}
