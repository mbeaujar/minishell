/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 19:50:33 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/04/30 20:15:22 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void display_buffer(t_prompt *prompt)
{
    ft_putstr_fd(prompt->buffer->buff, STDIN_FILENO);
    prompt->indice = prompt->buffer->strlen;
}

void display_prompt(t_prompt *prompt)
{
    ft_putstr_fd("minishell &> ", STDIN_FILENO);
    prompt->indice = 0;
}