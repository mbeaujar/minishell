/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 16:34:57 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/23 20:36:53 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int add_child_process(t_prompt *prompt, t_command *ptr, int in, int out)
{
    int pid;

    pid = fork();
    if (pid == -1)
        return (pid);
    if (pid == 0)
    {
        if (ptr->std_in == 0)
            dup2(in, 0);
        if (ptr->std_out == 1)
            dup2(out, 1);
        if (in != 0)
            close(in);
        if (out != 1)
            close(out);
        which_command(prompt, ptr, ptr->argv);
        kill(pid, 0);
        exit(pid);
    }
    return (pid);
}

void refill_std(int *std, int len, t_command *ptr)
{
    int fd[2];
    int i;
    (void)ptr;

    std[0] = 0;
    i = 1;
    while (i < (len * 2) - 1)
    {
        if (pipe(fd) == -1)
            return ((void)printf("merde\n"));
        std[i] = fd[1];
        i++;
        std[i] = fd[0];
        i++;
        fd[0] = 0;
        fd[1] = 1;
        ptr = ptr->next;
    }
    std[i] = 1;
}

void build_pipe(t_prompt *prompt, t_command *ptr)
{
    t_command *tmp;
    int len;
    int *std;
    int *pid;
    int status;
    int i;
    int fd;
    int cout[2];

    len = nbpipe(ptr);
    if (!len)
        return;
    tmp = ptr;
    printf("len : %d\n", len);
    std = malloc(sizeof(int) * ((len * 2)));
    if (!std)
        return ((void)printf("pitie\n"));
    refill_std(std, len, ptr);
    pid = malloc(sizeof(int) * len);
    if (!pid)
        return;
    i = 0;
    fd = 0;
    while (i < len)
    {
        cout[0] = std[fd++];
        cout[1] = std[fd++];
        redir(ptr);
        pid[i] = add_child_process(prompt, ptr, cout[0], cout[1]);
        if (cout[0] != 0)
            close(cout[0]);
        if (cout[1] != 1)
            close(cout[1]);
        close_redir(ptr);
        ptr = ptr->next;
        i++;
    }
    i = 0;
    while (i < len)
    {
        waitpid(pid[i], &status, 0);
        i++;
    }
    free(std);
}