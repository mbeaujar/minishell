/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 19:51:16 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/05 17:12:44 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** EAGAIN protect read timeout 
*/

char read_key(t_prompt *prompt)
{
    char c;
    int ret;

    ret = 0;
    errno = 0;
    while ((ret = read(STDIN_FILENO, &c, 1)) != 1)
    {
        if (ret == -1 && errno != EAGAIN)
        {
            printlstbuffer(prompt->buffer);
            g_buffer(FREE, NULL);
            freelstbuffer(&prompt->buffer);
            disablerawmode(prompt->orig_termios);
            exit(4);
        }
        errno = 0;
    }
    return (c);
}

void delete_char_prompt(t_prompt *prompt)
{
    if (prompt->indice > 0)
    {
        create_termcap("le");
        create_termcap("dc");
        decrease_buffer(prompt);
    }
}

void execute_commande(t_prompt *prompt)
{
    ft_putchar_fd('\n', STDOUT_FILENO);
    if (prompt->buffer->buff[0] != 0)
    {
        if (!prompt->buffer->previous)
        {
            prompt->buffer->modified = 0;
            cmd(prompt, ft_strdup(prompt->buffer->buff));
            lstaddfrontbuffer(&prompt->buffer, newlstbuffer(ft_calloc(10, sizeof(char))));
            g_buffer(FREE, NULL);
            g_buffer(SET, prompt->buffer);
        }
        else
        {
            //printlstbuffer(prompt->buffer);
            prompt->buffer->modified = 0;
            cmd(prompt, ft_strdup(prompt->buffer->buff));
            reset_buffer(prompt);
            //printlstbuffer(prompt->buffer);
            g_buffer(SET, prompt->buffer);
        }
    }
    if (prompt->setup.debug == 1)
    {
        printlstbuffer(prompt->buffer);
        ft_putchar_fd('\n', STDOUT_FILENO);
    }
    display_prompt(prompt);
}