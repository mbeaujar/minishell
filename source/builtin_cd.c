/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 14:09:30 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/04/18 16:48:51 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* void refresh_oldpwd(t_var *var)
{
	t_env *pwd;
	char *cwd;
	char *new_value;
	errno = 0;

	if (!(cwd = malloc(sizeof(char) * (PATH_MAX + 1))))
		return;
	if (getcwd(cwd, PATH_MAX))
	{
		new_value = refresh_value_pwd(cwd);
		if ((pwd = search_env(var->head, "OLDPWD")))
		{
			free(pwd->value);
			pwd->value = new_value;
			ft_putstr_fd("OLDPWD : ", 0);
			ft_putstr_fd(pwd->value, 0);
			ft_putstr_fd("\n", 0);
		}
		else
			create_pwd(var, new_value, "OLDPWD=");
	}
	else
	{
		free(cwd);
		printerrno();
	}
} */

void change_directory(t_var *var, char *path)
{
	char *ret_error;
	int ret;
	errno = 0;
	
	/*  refresh_oldpwd(var);*/
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

void cd(t_var *var, char *cmd)
{
	int i;
	t_env *home;
	int leak;

	i = 0;
	leak = 0;
	cmd = ft_strtrim(cmd, " ");
	while (cmd[i] && cmd[i] != ' ')
		i++;
	while (cmd[i] && cmd[i] == ' ')
		i++;
	if (cmd[i] == '~')
	{
		home = search_env(var->head, "HOME");
		if (home && home->value)
		{
			cmd = search_and_replace(cmd, "~", home->value, 0);
			leak = 1;
		}
	}
	if (cmd[i] == 0)
	{
		home = search_env(var->head, "HOME");
		if (home && home->value)
		{
			cmd = home->value;
			i = 0;
		}
		else
		{
			ft_putstr_fd("bash: cd: HOME not set\n", 0);
			return;
		}
	}
	printf("chemin de cd : '%s'\n", cmd + i);
	change_directory(var, cmd + i);
	if (leak)
		free(cmd);
}
