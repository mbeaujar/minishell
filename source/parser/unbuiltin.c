/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unbuiltin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 22:57:15 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/22 00:35:45 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** erreur ligne 29 avec un pipe c'est normal c'est la fct pipe le problème 
*/

void unbuiltin(t_prompt *prompt, t_command *ptr, char **args)
{
    int status;
    int pid;
    char **envp;

    envp = new_table_env(prompt->env);
    if (!envp)
        return ((void)printf("problem in the fct unbuiltin with char **envp\n"));
    if (!ptr->path)
        return ((void)printf("problem no path in the fct unbuiltin\n"));
    pid = fork();
    if (pid == -1)
        return ((void)printf("problem of pid in fct unbuiltin\n"));
    if (pid == 0)
    {
        status = execve(ptr->path, args, envp);
        if (status == -1)
            printerrno_fd(STDOUT_FILENO);
        kill(pid, 0);
        exit(status);
    }
    else
    {
        waitpid(pid, &status, 0);
        free(envp);
        free(ptr->path);
        ptr->path = NULL;
    }
}