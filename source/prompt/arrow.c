/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 19:47:29 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/06 18:40:51 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** H home F end
*/

void change_buffer(t_prompt *prompt, t_buff *new)
{
	g_buffer(FREE, NULL);
	prompt->buffer = new;
	g_buffer(SET, prompt->buffer);
	create_termcap("rc");
	create_termcap("ce");
	create_termcap("sc");
	ft_putstr_fd("minishell &> ", STDOUT_FILENO);
	display_buffer(prompt);
}

void move_to_start(t_prompt *prompt)
{
	while (prompt->indice > 0)
		move_left(prompt);
}

void move_to_end(t_prompt *prompt)
{
	while (prompt->indice < prompt->buffer->strlen)
		move_right(prompt);
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
	if (seq[0] == '[' && seq[1] == 'C' && (prompt->indice + 1) <= prompt->buffer->strlen)
		move_right(prompt);
	if (seq[0] == '[' && seq[1] == 'D' && (prompt->indice - 1) >= 0)
		move_left(prompt);
	if (seq[0] == '[' && seq[1] == 'H')
		move_to_start(prompt);
	if (seq[0] == '[' && seq[1] == 'F')
		move_to_end(prompt);
	return (is_ctrl_arrow(prompt, c, seq[0], seq[1]));
}

void new_line(t_prompt *prompt)
{
	int old_indice;
	int len;

	old_indice = prompt->indice + 1;
	create_termcap("rc");
	create_termcap("ce");
	display_prompt(prompt);
	display_buffer(prompt);
	len = prompt->buffer->strlen - old_indice;
	prompt->indice = old_indice - 1;
	while (len--)
		create_termcap("le");
}
