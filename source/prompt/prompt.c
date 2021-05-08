/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 19:15:27 by beaujardmae       #+#    #+#             */
/*   Updated: 2021/05/07 22:24:14 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void reset_buffer(t_prompt *prompt)
{
    t_buffer *old;
    t_buffer *new;

    old = g_buffer(GET, NULL);
    new = prompt->buffer;
    if (old->previous)
        old->previous->next = old;
    if (old->next)
        old->next->previous = old;
    while (prompt->buffer->previous)
        prompt->buffer = prompt->buffer->previous;
    free(prompt->buffer->buff);
    prompt->buffer->buff = new->buff;
    prompt->buffer->strlen = new->strlen;
    prompt->buffer->len = new->len;
    prompt->buffer->modified = new->modified;
    free(new);
    lstaddfrontbuffer(&prompt->buffer, newlstbuffer(ft_calloc(10, sizeof(char))));
}

void read_stdin(t_prompt *prompt)
{
    char c;
    
    display_prompt(prompt);
    prompt->buffer = newlstbuffer(ft_calloc(10, sizeof(char)));
    g_buffer(SET, prompt->buffer);
    while (1)
    {
        c = read_key(prompt);
        if (ft_isprint(c))
        {
            write(STDOUT_FILENO, &c, 1);
            expand_buffer(prompt, c);
        }
        if (c == DELETE)
            delete_char_prompt(prompt);
        isctrl(prompt, c);
        if (c == ARROW)
            c = arrow_key(c, prompt);
        if (c == ENTER)
            execute_commande(prompt);
    }
    freelstbuffer(&prompt->buffer);
}