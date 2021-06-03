/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 16:34:57 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/02 22:13:22 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_fork(t_prompt *prompt)
{
	int i;

	i = 0;
	freelstbuffer(&prompt->buffer);
	freelstenv(&prompt->env);
	freelstcommand(&prompt->list);
	freelstlexer(&prompt->lexer);
	g_buffer(FREE, NULL);
	while (prompt->std && i < prompt->len_pipe * 2)
	{
		if (prompt->std[i] != 0 && prompt->std[i] != 1 && prompt->std[i] != -1)
			close(prompt->std[i]);
		i++;
	}
	free(prompt->std);
	free(prompt->pid);
	secure_free(prompt->cmd);
}

int	add_child_process(t_prompt *prompt, t_cmd *ptr, int in, int out)
{
	int	pid;

	errno = 0;
	pid = fork();
	if (pid == -1)
		printerrno_fd(1);
	if (pid == -1)
		return (pid);
	if (pid == 0)
	{
		if (ptr->std_in == 0 && in != -1)
			dup2(in, 0);
		if (ptr->std_out == 1 && out != -1)
			dup2(out, 1);
		if (in != 0 && in != -1)
			close(in);
		if (out != 1 && out != -1)
			close(out);
		which_command(prompt, ptr, ptr->argv);
		free_fork(prompt);
		close(2);
		close(1);
		close(0);
		exit(pid);
	}
	return (pid);
}

void	refill_std(int *std, int len)
{
	int	fd[2];
	int	i;

	std[0] = 0;
	i = 1;
	while (i < (len * 2) - 1)
	{
		if (pipe(fd) == -1)
			return ((void)printf("error pipe\n"));
		std[i] = fd[1];
		i++;
		std[i] = fd[0];
		i++;
		fd[0] = 0;
		fd[1] = 1;
	}
	std[i] = 1;
}

void	exec_child_process(t_prompt *prompt, t_cmd *ptr, int *std, int *pid)
{
	int	len;
	int	i;
	int	fd;

	len = prompt->len_pipe;
	i = 0;
	fd = 0;
	while (i < len)
	{
		redir(ptr);
		pid[i] = add_child_process(prompt, ptr, std[fd], std[fd + 1]);
		if (std[fd] != 0 && std[fd] != 1 && std[fd] != -1)
			close(std[fd]);
		if (std[fd + 1] != 1 && std[fd + 1] != 0 && std[fd + 1] != -1)
			close(std[fd + 1]);
		close_redir(ptr);
		fd += 2;
		ptr = ptr->next;
		i++;
	}
	while (len)
	{
		waitpid(pid[i - len], &fd, 0);
		len--;
	}
}

void	build_pipe(t_prompt *prompt, t_cmd *ptr)
{
	int	len;
	int	*std;
	int	*pid;

	len = nbpipe(ptr);
	if (!len)
		return ;
	prompt->len_pipe = len;
	std = malloc(sizeof(int) * ((len * 2)));
	if (!std)
		return ((void)printf("problem malloc unbuiltin\n"));
	prompt->std = std;
	refill_std(std, len);
	pid = malloc(sizeof(int) * len);
	if (!pid)
		return ;
	prompt->pid = pid;
	exec_child_process(prompt, ptr, std, pid);
	free(pid);
	free(std);
	prompt->std = NULL;
	prompt->pid = NULL;
}
