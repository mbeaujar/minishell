/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_non_tty.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 17:19:23 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/01 17:37:29 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exit_tty(t_prompt *prompt)
{
    freelstenv(&prompt->env);
    exit(0);
}

void sighandler(int sig)
{
    (void)sig;
    printf("\n");
}

void prompt_non_tty(t_prompt *prompt)
{
    int ret;
    char *line;
    errno = 0;

    line = NULL;
    ret = 1;
    prompt->indice = 1;
    signal(SIGINT, sighandler);
    while (ret)
    {
        ret = get_next_line(0, &line);
        if (ret == 0)
            exit_tty(prompt);
        if (ret == -1)
        {
            printerrno_fd(1);
            exit_tty(prompt);
        }
        cmd(prompt, line);
        free(line);
        prompt->indice++;
    }
}