/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unbuiltin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 22:57:15 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/30 15:42:41 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** erreur ligne 29 avec un pipe c'est normal c'est la fct pipe le problème 
*/

int g_pid(int raw, int state)
{
    static int pid = -1;
    static int ret_errno = 0;

    if (state == GET)
        pid = raw;
    if (state == SET_ERRNO)
        ret_errno = raw;
    if (state == GET_ERRNO)
        return (ret_errno);
    return (pid);
}

void signalhandler(int sig)
{
    int pid;

    pid = g_pid(0, GET);
    if (pid == -1)
        return;
    if (sig == SIGINT)
    {
        printf("\n");
        kill(pid, 0);
    }
}

void exec_child(t_command *ptr, char **args, char **envp, int pid)
{
    int ret;
    errno = 0;

    g_pid(pid, SET);
    g_pid(0, SET_ERRNO);
    ret = execve(ptr->path, args, envp);
    if (ret == -1)
    {
        g_pid(125 + errno, SET_ERRNO);
        printerrno_fd(STDOUT_FILENO);
        kill(pid, 0);
        exit(125 + errno);
    }
}

void unbuiltin(t_prompt *prompt, t_command *ptr, char **args)
{
    int status;
    int pid;
    char **envp;

    envp = new_table_env(prompt->env);
    if (!envp)
        return ((void)printf("problem in the fct unbuiltin with char **envp\n"));
    if (!ptr->path || !args)
        return ((void)printf("problem no path in the fct unbuiltin\n"));
    signal(SIGINT, signalhandler);
    pid = fork();
    if (pid == -1)
        return ((void)printerrno_fd(1));
    if (pid == 0)
        exec_child(ptr, args, envp, pid);
    waitpid(pid, &status, 0);
    g_pid(-1, SET);
    prompt->returned = g_pid(0, GET_ERRNO);
    free(envp);
    free(ptr->path);
    ptr->path = NULL;
}