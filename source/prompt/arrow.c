/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 19:47:29 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/04 17:55:24 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void change_buffer(t_prompt *prompt, t_buffer *new)
{
    g_buffer(FREE, NULL);
    prompt->buffer = new;
    g_buffer(SET, prompt->buffer);
    create_termcap("dl");
    ft_putstr_fd("minishell &> ", STDIN_FILENO);
    display_buffer(prompt);
}

char arrow_key(char c, t_prompt *prompt)
{
    char seq[3];

    if ((read(STDIN_FILENO, &seq[0], 1)) != 1)
        return (c);
    if ((read(STDIN_FILENO, &seq[1], 1)) != 1)
        return (c);
    if (seq[0] == '[' && seq[1] == 'A' && prompt->buffer->next != NULL)
        change_buffer(prompt, prompt->buffer->next);
    if (seq[0] == '[' && seq[1] == 'B' && prompt->buffer->previous != NULL)
        change_buffer(prompt, prompt->buffer->previous);
    if (seq[0] == '[' && seq[1] == 'C' && (prompt->indice + 1) < prompt->buffer->strlen)
    {
        prompt->indice++;
        create_termcap("nd");
    }
    if (seq[0] == '[' && seq[1] == 'D' && (prompt->indice - 1) >= 0)
    {
        prompt->indice--;
        create_termcap("le");
    }
    return (c);
}