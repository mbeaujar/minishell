/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 15:23:57 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/07 17:26:30 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	refresh_prompt(t_prompt *prompt)
{
	int	old_indice;
	int	len;

	old_indice = prompt->indice;
	create_termcap("rc");
	create_termcap("ce");
	display_prompt(prompt);
	display_buffer(prompt);
	len = prompt->buffer->strlen - old_indice;
	prompt->indice = old_indice;
	while (len-- > 0)
		create_termcap("le");
}

void	new_word(t_prompt *prompt, char *prev, char *next)
{
	free(prompt->buffer->buff);
	prompt->buffer->buff = ft_strjoin_gnl(prev, next);
	free(next);
	prompt->buffer->strlen = (int)ft_strlen(prompt->buffer->buff);
	refresh_prompt(prompt);
}

void	cut_word(t_prompt *prompt)
{
	char	*prev;
	char	*next;

	if (prompt->a == -1 || prompt->b == -1)
		return ;
	if (prompt->a > prompt->b)
	{
		prev = ft_substr(prompt->buffer->buff, 0, prompt->b);
		next = ft_substr(prompt->buffer->buff, prompt->a,
				prompt->buffer->strlen - prompt->a);
	}
	else
	{
		prev = ft_substr(prompt->buffer->buff, 0, prompt->a);
		next = ft_substr(prompt->buffer->buff, prompt->b,
				prompt->buffer->strlen - prompt->b);
	}
	new_word(prompt, prev, next);
}

void	isctrl_bonus(t_prompt *prompt, char c)
{
	if (c == (('a') & 0x1f))
		prompt->a = prompt->indice;
	if (c == (('b') & 0x1f))
		prompt->b = prompt->indice;
	if (c == (('x') & 0x1f))
		cut_word(prompt);
	if (c == (('e') & 0x1f))
		find_word(prompt);
	if (c == (('p') & 0x1f))
		paste_word(prompt);
}
