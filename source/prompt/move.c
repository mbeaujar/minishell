/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 15:05:59 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/07 15:06:37 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	move_left(t_prompt *prompt)
{
	prompt->indice--;
	create_termcap("le");
}

void	move_right(t_prompt *prompt)
{
	prompt->indice++;
	create_termcap("nd");
}

void	move_to_start(t_prompt *prompt)
{
	while (prompt->indice > 0)
		move_left(prompt);
}

void	move_to_end(t_prompt *prompt)
{
	while (prompt->indice < prompt->buffer->strlen)
		move_right(prompt);
}
