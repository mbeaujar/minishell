/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unbuiltin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 22:57:15 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/29 19:41:36 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** erreur ligne 29 avec un pipe c'est normal c'est la fct pipe le problème 
*/

int g_pid(int raw, int state)
{
    static int pid = -1;

    if (state == GET)
        pid = raw;
    return (pid);
}

void signalhandler(int sig)
{
    int pid;

    pid = g_pid(0, GET);
    if (pid == -1)
        return;
    if (sig == SIGINT || sig == SIGQUIT)
    {
        printf("\n");
        kill(pid, 0);
    }
    if (sig == SIGQUIT)
        printf("core dump created.\n");
}

void signal_list(void)
{
    signal(SIGINT, signalhandler);
    signal(SIGQUIT, signalhandler);
}

void unbuiltin(t_prompt *prompt, t_command *ptr, char **args)
{
    int status;
    int pid;
    char **envp;
    errno = 0;

    envp = new_table_env(prompt->env);
    if (!envp)
        return ((void)printf("problem in the fct unbuiltin with char **envp\n"));
    if (!ptr->path || !args)
        return ((void)printf("problem no path in the fct unbuiltin\n"));
    disablerawmode(prompt->orig_termios);
    signal_list();
    pid = fork();
    if (pid == -1)
        return ((void)printerrno_fd(1));
    if (pid == 0)
    {
        g_pid(pid, SET);
        status = execve(ptr->path, args, envp);
        if (status == -1)
            printerrno_fd(STDOUT_FILENO);
        kill(pid, 0);
        exit(status);
    }
    waitpid(pid, &status, 0);
    enablerawmode(prompt->raw);
    g_pid(-1, SET);
    free(envp);
    free(ptr->path);
    ptr->path = NULL;
}