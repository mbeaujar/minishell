/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 19:51:16 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/01 00:13:22 by mbeaujar         ###   ########.fr       */
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
            if (prompt->modified)
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
    if (prompt->buffer->buff[0] != 0)
    {
        if (!prompt->buffer->previous)
        {
            lstaddfrontbuffer(&prompt->buffer, newlstbuffer(ft_calloc(10, sizeof(char))));
            g_buffer(FREE, NULL);
            g_buffer(SET, prompt->buffer);
        }
        else
        {
            reset_buffer(prompt);
            g_buffer(SET, prompt->buffer);
        }
    }
    printf("\n");
    printlstbuffer(prompt->buffer);
    ft_putchar_fd('\n', STDIN_FILENO);
    display_prompt(prompt);
    prompt->modified = 1;
}