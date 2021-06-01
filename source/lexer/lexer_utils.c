/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 17:45:45 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/01 18:27:05 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	escape_space(char *str, int *i, int state)
{
	if (state == 1)
	{
		if (str[*i] == ' ' && *i == 0)
		{
			while (str[*i] && str[*i] == ' ')
				(*i)++;
		}
	}
	else
	{
		while (str[*i] && str[*i] == ' ')
			(*i)++;
	}
}

void	new_token(t_lexer **head, char *buffer, int len, int *y)
{
	buffer[*y] = 0;
	lstaddbacklexer(head, newlstlexer(ft_strdup(buffer), DEFAULT));
	ft_bzero(buffer, len);
	*y = 0;
}

void	token_backslash(char *str, int *i, char sep)
{
	if (sep != '\'' && str[*i] == '\\')
	{
		if (str[*i + 1])
			str[*i + 1] = -str[*i + 1];
		if (sep == 0 && str[*i + 1])
			(*i)++;
		if ((sep == '"' && str[*i + 1] == -34)
			|| (sep == '"' && str[*i + 1] == -92))
			(*i)++;
	}
	if (sep == '\'' && sep != str[*i])
		str[*i] = -str[*i];
	if (sep != 0)
	{
		if (sep == '"' && (str[*i] == '<'
				|| str[*i] == '>' || str[*i] == ';' || str[*i] == '|'))
			str[*i] = -str[*i];
	}
}

int	is_sep(char c)
{
	return (c == '\\' || c == '"' || c == '\'' || c == '$'
		|| c == '>' || c == '<' || c == '|' || c == ';');
}
