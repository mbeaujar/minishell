/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 14:09:30 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/04/15 22:25:12 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void change_directory(t_var *var, char *path)
{
	char *ret_error;
	int ret;
	errno = 0;
	
	if ((ret = chdir(path)) == -1)
	{
		ret_error = strerror(errno);
		ft_putstr_fd(ret_error, 0);
		return ;
	}
	refresh_pwd(var);
}

void cd(t_var *var, char *cmd)
{
	int i;

	i = 0;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	while (cmd[i] && cmd[i] == ' ')
		i++;
	printf("chemin de cd : %s\n", cmd + i);
	change_directory(var, cmd + i);
}
