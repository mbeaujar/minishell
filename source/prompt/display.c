/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 19:50:33 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/25 00:29:58 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** sauvegarde la position du cursor --- sc
** restaure la position du cursor enregistrée -- rc 
** del la fin de la ligne -- ce
*/

void display_buffer(t_prompt *prompt)
{
    printbuffer(prompt->buffer->buff);
    prompt->indice = prompt->buffer->strlen;
}

void display_prompt(t_prompt *prompt)
{
    create_termcap("sc");
    ft_putstr_fd("minishell &> ", STDOUT_FILENO);
    prompt->indice = 0;
}