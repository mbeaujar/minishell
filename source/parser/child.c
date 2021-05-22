/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 16:34:57 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/22 18:02:21 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int add_child_process(t_prompt *prompt, t_command *ptr, int fd[2])
{
    int pid;

    pid = fork();
    if (pid == -1)
        return (pid);
    if (pid == 0)
    {
        if (ptr->std_in == 0 && fd[0] != 0)
        {
            dup2(fd[0], 0);
            printf("---  fd 0 : %d\n", fd[0]);
        }
        if (ptr->std_out == 1 && fd[1] != 1)
        {
            printf("---  fd 1 : %d\n", fd[1]);
            dup2(fd[1], 1);
        }
        close(fd[0]);
        close(fd[1]);
        which_command(prompt, ptr, ptr->argv);
        kill(pid, 0);
        exit(pid);
    }
    return (pid);
}

int *fill_std(int len)
{
    int *std;
    int fd[2];
    int i;

    std = malloc(sizeof(int) * ((len * 2) + 1));
    if (!std)
        return (NULL);
    i = 1;
    std[0] = 0;
    while ((i + 2) <= len + 1)
    {
        pipe(fd); // to secure
        std[i++] = fd[0];
        std[i++] = fd[1];
        //printf("fd 0 : %d\tfd 1 : %d\n", fd[0], fd[1]);
    }
    std[i] = 1;
    return (std);
}

void build_pipe(t_prompt *prompt, t_command *ptr)
{
    int fd[2];
    int *std;
    int *pointer;
    int *pids;
    int status;
    int len;
    int i;

    len = nbpipe(ptr, prompt);
    if (!len)
        return;
    pids = malloc(sizeof(int) * len);
    if (!pids)
        return;
    std = fill_std(len);
    if (!std)
        return;
    pointer = std;
    i = 0;
    (void)fd;
    display_all_pipe_fd(std, len);
    printf("\n");
    while (i < len)
    {
        fd[0] = *std++;
        fd[1] = *std++;
        printf("fd 0 : %d\tfd 1 : %d\nin : %d\t\tout : %d\n", fd[0], fd[1], ptr->std_in, ptr->std_out);
        pids[i] = add_child_process(prompt, ptr, fd);
        ptr = ptr->next;
        i++;
    }
    i = 0;
    while (i < len)
    {
        if (pointer[i] != 0 && pointer[i] != 1)
            close(pointer[i]);
        i++;
    }
    i = 0;
    (void)status;
    while (i < len)
    {
        waitpid(pids[i], &status, 0);
        i++;
    }
    free(pointer);
    free(pids);
}