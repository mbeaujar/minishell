/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 16:34:57 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/01 20:37:59 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (ptr->std_in == 0)
			dup2(in, 0);
		if (ptr->std_out == 1)
			dup2(out, 1);
		if (in != 0)
			close(in);
		if (out != 1)
			close(out);
		which_command(prompt, ptr, ptr->argv);
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
			return ((void)printf("merde\n"));
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

	len = nbpipe(ptr);
	i = 0;
	fd = 0;
	while (i < len)
	{
		redir(ptr);
		pid[i] = add_child_process(prompt, ptr, std[fd], std[fd + 1]);
		if (std[fd] != 0)
			close(std[fd]);
		if (std[fd + 1] != 1)
			close(std[fd + 1]);
		fd += 2;
		close_redir(ptr);
		ptr = ptr->next;
		i++;
	}
	while (len)
	{
		waitpid(pid[len - i], &fd, 0);
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
	std = malloc(sizeof(int) * ((len * 2)));
	if (!std)
		return ((void)printf("problem malloc unbuiltin\n"));
	refill_std(std, len);
	pid = malloc(sizeof(int) * len);
	if (!pid)
		return ;
	exec_child_process(prompt, ptr, std, pid);
	free(pid);
	free(std);
}
