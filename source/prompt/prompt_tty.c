/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_tty.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 17:19:23 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/31 22:02:08 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exit_tty(t_prompt *prompt)
{
    ft_putstr_fd("exit\n", 1);
    freelstenv(&prompt->env);
    exit(0);
}

void sighandler(int sig)
{
    (void)sig;
    printf("\n");
    ft_putstr_fd("minishell &> ", 1);
}

void prompt_tty(t_prompt *prompt)
{
    int ret;
    char *line;

    line = NULL;
    ret = 1;
    signal(SIGINT, sighandler);
    while (ret)
    {
        ft_putstr_fd("minishell &> ", 1);
        ret = get_next_line(0, &line);
        if (ret == 0)
            exit_tty(prompt);
        if (ret == -1)
            exit_tty(prompt);
        cmd(prompt, line);
        free(line);
    }
}