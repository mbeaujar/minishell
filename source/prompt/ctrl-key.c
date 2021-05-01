/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl-key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 18:39:11 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/01 00:37:24 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ctrl-c affiche ^C et crée un nouvueau prompt -- free le buffer et check si le buffer est vide
// ctrl-d appel la fonction exit si il n'y a rien d'écrit dans le prompt sinon ne fais rien

// #define CTRL_KEY(k) ((k) & 0x1f)

// alt + left == ^[b

void recup_old_buffer(t_prompt *prompt)
{
    t_buffer *old;

    old = g_buffer(GET, NULL);
    old->next = prompt->buffer->next;
    old->previous = prompt->buffer->previous;
    if (old->previous)
        old->previous->next = old;
    if (old->next)
        old->next->previous = old;
    free(prompt->buffer->buff);
    prompt->buffer = old;
}

void isctrl(t_prompt *prompt, char c)
{
    if (c == (('c') & 0x1f))
    {
        write(STDIN_FILENO, "^C\n", 3);
        if (!prompt->buffer->previous)
            prompt->buffer->buff[0] = 0;
        else
            recup_old_buffer(prompt);
        while (prompt->buffer->previous)
            prompt->buffer = prompt->buffer->previous;
        display_prompt(prompt);
    }
    if (c == (('d') & 0x1f) && prompt->buffer->buff[0] == 0)
    {
        write(STDIN_FILENO, "exit\n", 6);
        freelstbuffer(prompt->buffer);
        disablerawmode(prompt->orig_termios);
        exit(3);
    }
    if (c == (('l') & 0x1f))
    {
        create_termcap("cl");
        display_prompt(prompt);
        display_buffer(prompt);
    }
}

t_buffer *g_buffer(int state, t_buffer *buffer)
{
    static t_buffer *global = NULL;

    if (state == 1)
    {
        if (!(global = malloc(sizeof(t_buffer) * 1)))
            return (NULL);
        global->buff = ft_strdup(buffer->buff);
        global->len = buffer->len;
        global->modified = buffer->modified;
        global->strlen = buffer->strlen;
        global->next = buffer->next;
        global->previous = buffer->previous;
    }
    if (state == 2)
    {
        if (global != NULL)
        {
            free(global->buff);
            free(global);
        }
    }
    return (global);
}