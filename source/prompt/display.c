/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 19:50:33 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/06 18:29:34 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void display_buffer(t_prompt *prompt)
{
    printbuffer(prompt->buffer->buff);
    prompt->indice = prompt->buffer->strlen - 1;
}

void display_prompt(t_prompt *prompt)
{
    ft_putstr_fd("minishell &> ", STDIN_FILENO);
    prompt->indice = 0;
}