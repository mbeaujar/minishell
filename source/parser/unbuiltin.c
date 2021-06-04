/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unbuiltin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 22:57:15 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/04 14:28:29 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_pid(int raw, int state)
{
	static int	pid = -1;
	static int	ret_errno = 0;

	if (state == GET)
		pid = raw;
	if (state == SET_ERRNO)
		ret_errno = raw;
	if (state == GET_ERRNO)
		return (ret_errno);
	return (pid);
}

void	signalhandler(int sig)
{
	int	pid;

	pid = g_pid(0, GET);
	if (pid == -1)
		return ;
	if (sig == SIGINT)
	{
		printf("\n");
		kill(pid, 0);
	}
}

void	exec_child(t_cmd *ptr, t_prompt *prompt, char **envp, int pid)
{
	int	ret;

	errno = 0;
	g_pid(pid, SET);
	ret = execve(ptr->path, prompt->args, envp);
	if (ret == -1)
	{
		free_fork(prompt);
		if (errno == EACCES)
		{
			ft_putstr_fd("bash: ", 1);
			ft_putstr_fd(ptr->path, 1);
			ft_putstr_fd(": ", 1);
			printerrno_fd(STDOUT_FILENO);
			close(1);
			exit(126);
		}
		printerrno_fd(STDOUT_FILENO);
		close(1);
		exit(125 + errno);
	}
}

void	unbuiltin(t_prompt *prompt, t_cmd *ptr, char **args)
{
	int		status;
	int		pid;
	char	**envp;

	envp = new_table_env(prompt->env);
	if (!envp)
		return ((void)printf("problem in the fct unbuiltin with char **envp\n"));
	if (!ptr->path || !args)
		return ((void)printf("problem no path in the fct unbuiltin\n"));
	signal(SIGINT, signalhandler);
	prompt->args = args;
	pid = fork();
	if (pid == -1)
		return ((void)printerrno_fd(1));
	if (pid == 0)
		exec_child(ptr, prompt, envp, pid);
	waitpid(pid, &status, 0);
	g_pid(-1, SET);
	prompt->returned = WEXITSTATUS(status);
	free_tab(envp);
	free(ptr->path);
	ptr->path = NULL;
}
