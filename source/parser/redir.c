/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 19:04:07 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/02 22:22:30 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_errno(int ret)
{
	if (ret == -1)
		printerrno_fd(1);
	errno = 0;
	return (ret);
}

void	redir(t_cmd *ptr)
{
	int	fd_out;
	int	fd_in;

	errno = 0;
	if (ptr->std_out != 1 && ptr->std_out != -1)
	{
		fd_out = check_errno(dup(1));
		check_errno(dup2(ptr->std_out, 1));
		close(ptr->std_out);
		ptr->std_out = fd_out;
	}
	if (ptr->std_in != 0 && ptr->std_in != -1)
	{
		fd_in = check_errno(dup(0));
		check_errno(dup2(ptr->std_in, 0));
		close(ptr->std_in);
		ptr->std_in = fd_in;
	}
}

void	close_redir(t_cmd *ptr)
{
	errno = 0;
	if (ptr->std_out != 1 && ptr->std_out != -1)
	{
		check_errno(dup2(ptr->std_out, 1));
		close(ptr->std_out);
		ptr->std_out = 1;
	}
	if (ptr->std_in != 0 && ptr->std_in != -1)
	{
		check_errno(dup2(ptr->std_in, 0));
		close(ptr->std_in);
		ptr->std_in = 0;
	}
}
