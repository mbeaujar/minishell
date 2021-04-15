/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:19:32 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/04/15 22:15:51 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	free(cwd);
	return (new_value);
}

void create_pwd(t_var *var, char *cwd)
{
	char *env;

	if (!(env = malloc(sizeof(char) * (4 + (int)ft_strlen(cwd) + 1))))
		return;
	ft_strlcpy(env, "PWD=", 4);
	ft_strjoin(env, cwd);
	free(cwd);
	addlstenv(&var->head, env);
	t_env *pwd;

	pwd = search_env(var->head, "PWD");
	ft_putstr_fd("NEW PWD : ", 0);
	ft_putstr_fd(pwd->value, 0);
	ft_putstr_fd("\n", 0);
}

void refresh_pwd(t_var *var)
{
	t_env *pwd;
	char *cwd;
	char *new_value;
	errno = 0;

	if (!(cwd = malloc(sizeof(char) * (PATH_MAX + 1))))
		return;
	getcwd(cwd, sizeof(cwd)); 
	//if (getcwd(cwd, sizeof(cwd)))
	//{
		new_value = refresh_value_pwd(cwd);
		if ((pwd = search_env(var->head, "PWD")))
		{
			free(pwd->value);
			pwd->value = new_value;
			ft_putstr_fd("NEW PWD : ", 0);
			ft_putstr_fd(pwd->value, 0);
			ft_putstr_fd("\n", 0);
			//printf("NEW PWD : %s\n", pwd->value);
		}
		else
			create_pwd(var, new_value);
	}
	//else
	//	printerrno();
}

void pwd(t_env *head)
{
	t_env *pwd;
	
	if ((pwd = search_env(head, "PWD")) == NULL)
		return;
	ft_putstr_fd(pwd->value, 0);
	ft_putstr_fd("\n", 0);
}