/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 21:41:05 by beaujardmae       #+#    #+#             */
/*   Updated: 2021/06/05 13:06:58 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_size_buffer(t_prompt *prompt, char c, char *str, int len)
{
	char	*new;
	int		i;
	int		j;

	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (str);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] > 0)
		{
			if (j == prompt->indice)
				new[j++] = c;
			new[j] = str[i];
			j++;
		}
		i++;
	}
	if (j == prompt->indice)
		new[j++] = c;
	new[j] = 0;
	free(str);
	return (new);
}

int	garbage_count(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str < 0)
			count++;
		str++;
	}
	return (count);
}

void	expand_buffer(t_prompt *prompt, char c)
{
	if (prompt->buffer->strlen + 1 >= prompt->buffer->len)
	{
		if (garbage_count(prompt->buffer->buff) < prompt->buffer->len / 2)
			prompt->buffer->len *= 2;
		prompt->buffer->buff = new_size_buffer(prompt, c,
				prompt->buffer->buff, prompt->buffer->len);
		prompt->buffer->strlen = (int)ft_strlen(prompt->buffer->buff);
		new_line(prompt);
	}
	else if (prompt->indice == prompt->buffer->strlen)
	{
		prompt->buffer->buff[prompt->buffer->strlen++] = c;
		prompt->buffer->buff[prompt->buffer->strlen] = 0;
	}
	else
	{
		prompt->buffer->buff = new_size_buffer(prompt, c,
				prompt->buffer->buff, prompt->buffer->len);
		prompt->buffer->strlen = (int)ft_strlen(prompt->buffer->buff);
		new_line(prompt);
	}
	prompt->buffer->modified = 1;
	prompt->indice++;
}

char	*delete_char_buffer(char *str, int len)
{
	char	*new;
	int		i;
	int		j;

	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (str);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] > 0)
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = 0;
	free(str);
	return (new);
}

void	decrease_buffer(t_prompt *prompt)
{
	int	normi;

	normi = prompt->indice - 1;
	prompt->buffer->buff[normi] = -prompt->buffer->buff[normi];
	if (prompt->buffer->strlen < ((prompt->buffer->len) / 4)
		&& ((prompt->buffer->len) / 4) > 10)
	{
		prompt->buffer->buff = delete_char_buffer(prompt->buffer->buff,
				prompt->buffer->len / 4);
		prompt->buffer->len /= 4;
	}
	prompt->buffer->modified = 1;
	prompt->buffer->strlen -= 1;
	prompt->indice--;
	if (prompt->buffer->strlen == 0)
		prompt->buffer->buff[0] = 0;
}
