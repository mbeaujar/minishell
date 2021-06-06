/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl-arrow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 13:49:37 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/06 14:34:23 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** [1;5D     [1;5C
*/

void    search_word_left(t_prompt *prompt)
{
    int len;

    len = 0;
    if (prompt->indice == 0)
        return ;
    while (prompt->buffer->buff[prompt->indice] == ' ' && prompt->indice - 1 > 0)
    {
        prompt->indice--;
        len++;
    }
    while (prompt->buffer->buff[prompt->indice] != ' ' && prompt->indice - 1 > 0)
    {
        prompt->indice--;
        len++;
    }
    while (len)
    {
        create_termcap("le");
        len--;
    }
}

char is_ctrl_arrow(t_prompt *prompt, char c, char first, char second)
{
    char seq[3];
    (void)prompt;

    if (first != '[' || second != '1')
        return (c);
    if ((read(0, &seq[0], 1) != 1))
        return (c);
    if ((read(0, &seq[1], 1) != 1))
        return (c);
    if ((read(0, &seq[2], 1) != 1))
        return (c);
    if (seq[0] == ';' && seq[1] == '5' && seq[2] == 'D')
        search_word_left(prompt);
    if (seq[0] == ';' && seq[1] == '5' && seq[2] == 'C')
        printf("non\n");
    return (c);
}