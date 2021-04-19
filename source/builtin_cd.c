/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 14:09:30 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/04/19 00:14:38 by mbeaujar         ###   ########.fr       */
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

// cd sans argument et ~ : dirige au path de la variable $HOME
// cd /

void cd(t_var *var, char *path)
{
	int i;
	t_env *home;
	int leak;

	i = 0;
	leak = 0;
	path = ft_strtrim(path, " ");
	while (path[i] && path[i] != ' ')
		i++;
	while (path[i] && path[i] == ' ')
		i++;
	if (path[i] == '~')
	{
		home = search_env(var->head, "HOME");
		if (home && home->value)
		{
			path = search_and_replace(path, "~", home->value, 0);
			leak = 1;
		}
	}
	if (path[i] == 0)
	{
		home = search_env(var->head, "HOME");
		if (home && home->value)
		{
			path = home->value;
			i = 0;
		}
		else
		{
			ft_putstr_fd("bash: cd: HOME not set\n", 0);
			return;
		}
	}
	printf("chemin de cd : '%s'\n", path + i);
	change_directory(var, path + i);
	if (leak)
		free(path);
}
