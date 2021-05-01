/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:40:30 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/04/22 15:09:54 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void display_prompt(void)
{
	ft_putstr_fd("minishell $> ", 0);
}

void ls_for_check(char *str, char **envp)
{
	char **args;
	int pid;

	args = malloc(sizeof(char*) * (2));
	args[0] = str;
	args[1] = 0;
	pid = -1;
	pid = fork();
	if (pid == 0)
	{
		execve("/bin/ls", args, envp);
		exit(0);
	}
	wait(&pid);
	free(args);
}

void prompt(t_var *var, char **envp)
{
	int ret;
	char *str;

	ret = 1;
	str = NULL;
	while (ret)
	{
		display_prompt();
		ret = get_next_line(0, &str);
		if (ret == -1)
		{
			// Tout free avant l'exit
			freelstenv(var->head);
			exit(1);
		}
		if (ret == 0)
		{
			// Tout free avant l'exit
			freelstenv(var->head);
			ft_putstr_fd("exit\n", 0);
			exit(2);
		}
		if (!ft_strncmp(str, "echo $?", 8))
			printf("echo $? = %d\n", errno);
		if (!ft_strncmp(str, "cd", 2))
			cd(var, str);
		if (!ft_strncmp(str, "pwd", 4))
			pwd(var->head);
		if (str[0] == 'l' && str[1] == 's')
			ls_for_check(str, envp);
		if (!ft_strncmp(str, "unset ", 6))
			unset(var, str);
			
		printf("'%s'\n", str);
		free(str);
	}
}
