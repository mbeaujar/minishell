/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 15:21:58 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/07 17:28:47 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_word(t_prompt *prompt)
{
	char	*word;

	if (prompt->a == -1 || prompt->b == -1)
		return ;
	if (prompt->a > prompt->b)
		word = ft_substr(prompt->buffer->buff,
				prompt->b, prompt->a - prompt->b);
	else
		word = ft_substr(prompt->buffer->buff,
				prompt->a, prompt->b - prompt->a);
	secure_free(prompt->word);
	prompt->word = word;
}

static void	refresh_prompt(t_prompt *prompt)
{
	int	old_indice;
	int	len_word;
	int	len;

	old_indice = prompt->indice;
	len_word = (int)ft_strlen(prompt->word);
	create_termcap("rc");
	create_termcap("ce");
	display_prompt(prompt);
	display_buffer(prompt);
	len = prompt->buffer->strlen - old_indice - len_word;
	prompt->indice = old_indice + len_word;
	while (len-- > 0)
		create_termcap("le");
}

void	paste_word(t_prompt *prompt)
{
	char	*prev;
	char	*next;

	if (prompt->word == NULL)
		return ;
	prev = ft_substr(prompt->buffer->buff, 0, prompt->indice);
	next = ft_substr(prompt->buffer->buff, prompt->indice,
			prompt->buffer->strlen - prompt->indice);
	prev = ft_strjoin_gnl(prev, prompt->word);
	secure_free(prompt->buffer->buff);
	prev = ft_strjoin_gnl(prev, next);
	secure_free(next);
	prompt->buffer->buff = prev;
	prompt->buffer->strlen = (int)ft_strlen(prompt->buffer->buff);
	if (prompt->buffer->strlen > prompt->buffer->len)
		prompt->buffer->len *= 2;
	refresh_prompt(prompt);
}
