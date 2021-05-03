/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 15:50:37 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/03 21:21:10 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** fonction pour debug cd
** fonction type pour les commandes non builtin
*/

void ls_for_check(t_prompt *prompt, char *str)
{
	char **args;
	int pid;
    char **envp;

    envp = new_table_env(prompt->env);
	args = malloc(sizeof(char*) * (2));
	args[0] = str;
	args[1] = 0;
	pid = -1;
	pid = fork();
	if (pid == 0)
	{
		execve("/bin/ls", args, envp);
		exit(0);
	}
	wait(&pid);
	free(args);
    free_tab(envp);
}


/*
** affiche le message d'errno
*/

void printerrno_fd(int fd)
{
    char *ret_error;

    ret_error = strerror(errno);
    ft_putendl_fd(ret_error, fd);
    return ;
}

/*
** chaque commande envoyé dans le prompt arrive ici 
** cmd est une copie avec strdup 
*/

void cmd(t_prompt *prompt, char *cmd)
{
    t_env *search;

    if (prompt->setup.debug == 1)
        printf("\nla commande : '%s'\n", cmd);
    if (ft_strncmp(cmd, "cd", 2) == 0)
        cd(prompt, cmd);
    // debug check OLDPWD
    if (ft_strncmp(cmd, "echo $OLDPWD", 12) == 0)
    {
        search = search_env(prompt->env, "OLDPWD");
        if (search)
            printf("name : '%s' value : '%s'\n", search->name, search->value);
        else
            printf("NULL\n");
    }
    // debug check PWD
    if (ft_strncmp(cmd, "echo $PWD", 9) == 0)
    {
        search = search_env(prompt->env, "PWD");
        if (search)
            printf("name : '%s' value : '%s'\n", search->name, search->value);
        else
            printf("NULL\n");
    }
    // debug check cd
    if (ft_strncmp(cmd, "ls", 2) == 0)
        ls_for_check(prompt, cmd);
    if (ft_strncmp(cmd, "unset", 5) == 0)
        unset(prompt, cmd);
    if (ft_strncmp(cmd, "pwd", 3) == 0)
        pwd();
    free(cmd);
}