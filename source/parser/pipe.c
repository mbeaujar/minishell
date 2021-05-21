/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:55:34 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/22 00:22:53 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Si stdout de la première commande ou stdin de la 2ème est redirigé alors ne pas modifié
**
** echo salut > test | cat
** écris salut dans test et n'affiche rien
**
** echo salut | cat < Makefile
** affiche Makefile dans le term
**
** echo salut | cat | cat 
** affiche salut
**
** echo salut | cat | cat | echo 
** affiche un retour à la ligne
**
** echo salut | cat | echo | cat
** affiche un retour à la ligne
*/

/*
** fd[0] = lecture
** fd[1] = écriture
**
** valgrind --track-fds=yes
*/

void exec_pipe(t_prompt *prompt, t_command *ptr, t_command *next)
{
    int pid[2];
    int fd[2];
    int status;

    if (pipe(fd) == -1)
        return ((void)printf("pipe error\n"));
    redir(ptr);
    redir(next);
    pid[0] = fork();
    if (pid[0] == -1)
        return ((void)printf("first child error\n"));
    if (pid[0] == 0) // premier child
    {
        if (ptr->std_out == 1)
            dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        which_command(prompt, ptr, ptr->argv);
        kill(pid[0], 0);
        exit(9);
    }
    else
    {
        pid[1] = fork();
        if (pid[1] == -1)
            return ((void)printf("second child error\n"));
        if (pid[1] == 0) // deuxième child
        {
            if (next->std_in == 0)
                dup2(fd[0], 0);
            close(fd[1]);
            close(fd[0]);
            which_command(prompt, next, next->argv);
            kill(pid[1], 0);
            exit(10);
        }
        else // parent
        {
            close(fd[0]);
            close(fd[1]);
            waitpid(pid[0], &status, 0);
            waitpid(pid[1], &status, 0);
            close_redir(ptr);
            close_redir(next);
        }
    }

    
}