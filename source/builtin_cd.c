/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 14:09:30 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/04/14 17:03:36 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** actualise la variable d'environnement PWD
*/

void refresh_pwd(t_env *head)
{
	char *cwd;
	t_env *pwd;
	errno = 0;

	if (!(cwd = malloc(sizeof(char) * (PATH_MAX + 1))))
		return;
	pwd = search_env(head, "PWD");
	if (getcwd(cwd, sizeof(cwd)))
	{
		free(pwd->value);
		pwd->value = cwd;
	}
}

/*
** Execute la commande cd
*/

void change_directory(t_env *head, char *path)
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
	refresh_pwd(head);
}

/*
** Parse la commande pour récupérer le path
*/

void cd(t_env *head, char *cmd)
{
	int i;

	i = 0;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	while (cmd[i] && cmd[i] == ' ')
		i++;
	printf("chemin de cd : %s\n", cmd + i);
	change_directory(head, cmd + i);
}

