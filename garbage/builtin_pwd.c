/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:19:32 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/04/21 21:15:42 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** string malloc to PATH_MAX + 1 -----> string malloc to len of the string
*/

void printerrno(void)
{
	char *error;

	error = strerror(errno);
	ft_putstr_fd(error, 0);
	ft_putchar_fd('\n', 0);
}

char *refresh_value_pwd(char *cwd)
{
	char *new_value;
	int i;

	i = 0;
	while (cwd[i])
		i++;
	if (!(new_value = malloc(sizeof(char) * (i + 1))))
		return (cwd);
	i = 0;
	while (cwd[i])
	{
		new_value[i] = cwd[i];
		i++;
	}
	new_value[i] = 0;
	free(cwd);
	return (new_value);
}

void create_pwd(t_var *var, char *cwd, char *name)
{
	char *env;

	if (!(env = malloc(sizeof(char) * (4 + (int)ft_strlen(cwd) + 1))))
		return;
	ft_strlcpy(env, name, (int)ft_strlen(name));
	ft_strjoin(env, cwd);
	free(cwd);
	addlstenv(&var->head, env);
}

void refresh_pwd(t_var *var)
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
		if ((pwd = search_env(var->head, "PWD")))
		{
			free(pwd->value);
			pwd->value = new_value;
			ft_putstr_fd("NEW PWD : ", 0);
			ft_putstr_fd(pwd->value, 0);
			ft_putstr_fd("\n", 0);
		}
		else
			create_pwd(var, new_value, "PWD=");
	}
	else
	{
		free(cwd);
		printerrno();
	}
}

void pwd(t_env *head)
{
	t_env *pwd;
	
	if ((pwd = search_env(head, "PWD")) == NULL)
		return;
	ft_putstr_fd(pwd->value, 0);
	ft_putstr_fd("\n", 0);
}