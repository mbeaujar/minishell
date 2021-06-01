/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl-key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 18:39:11 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/01 20:38:52 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	recup_old_buffer(t_prompt *prompt)
{
	t_buff	*old;

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

void	leave(t_prompt *prompt)
{
	g_buffer(FREE, NULL);
	write(STDOUT_FILENO, "exit\n", 5);
	freelstbuffer(&prompt->buffer);
	freelstenv(&prompt->env);
	disablerawmode(prompt->orig_termios);
	exit(0);
}

void	isctrl(t_prompt *prompt, char c)
{
	if (c == (('c') & 0x1f))
	{
		write(STDOUT_FILENO, "^C\n", 3);
		if (!prompt->buffer->previous)
			prompt->buffer->buff[0] = 0;
		else
			recup_old_buffer(prompt);
		while (prompt->buffer->previous)
			prompt->buffer = prompt->buffer->previous;
		display_prompt(prompt);
	}
	if (c == (('d') & 0x1f) && prompt->buffer->buff[0] == 0)
		leave(prompt);
	if (c == (('l') & 0x1f))
	{
		create_termcap("cl");
		display_prompt(prompt);
		display_buffer(prompt);
	}
}

t_buff	*g_buffer(int state, t_buff *buffer)
{
	static t_buff	*global = NULL;

	if (state == SET)
	{
		global = malloc(sizeof(t_buff) * 1);
		if (!global)
			return (NULL);
		global->buff = ft_strdup(buffer->buff);
		global->len = buffer->len;
		global->modified = buffer->modified;
		global->strlen = buffer->strlen;
		global->next = buffer->next;
		global->previous = buffer->previous;
	}
	if (state == FREE)
	{
		if (global != NULL)
		{
			free(global->buff);
			global->buff = NULL;
			free(global);
			global = NULL;
		}
	}
	return (global);
}
