/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 18:26:38 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/01 18:35:17 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	extra_token_sep(char *str, int *i, char *sep, int *var)
{
	if (*i == 0)
	{
		if ((*sep == 0 && str[*i] == '"') || (*sep == 0 && str[*i] == '\''))
		{
			*sep = str[*i];
			if (!str[*i + 1])
				return (0);
			(*i)++;
		}
	}
	if ((*sep == 0 && str[*i] == '"' && str[*i - 1] != '\\')
		|| (*sep == 0 && str[*i] == '\'' && str[*i - 1] != '\\'))
	{
		*sep = str[*i];
		if (!str[*i + 1])
			return (0);
		(*i)++;
		if (*var == 1 && !is_sep(str[*i]))
		{
			str[*i] = -str[*i];
			*var = 0;
		}
	}
	return (1);
}

int	token_sep(char *str, int *i, char *sep, int *var)
{
	if ((*i > 0 && *sep == '"' && str[*i] == '"' && str[*i - 1] != '\\')
		|| (*i > 0 && *sep == '\'' && str[*i] == '\''))
	{
		*sep = 0;
		(*i)++;
		if (*var == 1 && !is_sep(str[*i]))
		{
			str[*i] = -str[*i];
			*var = 0;
		}
	}
	return (extra_token_sep(str, i, sep, var));
}

int	lexer_error(char sep)
{
	if (sep != 0)
	{
		ft_putstr_fd("bash: syntax error multiline\n", STDOUT_FILENO);
		return (0);
	}
	return (1);
}

int	extra_token_type(t_lexing *var, t_lexer **head)
{
	char	c;

	c = 0;
	if (var->buffer && var->buffer[0] != 0)
		new_token(head, var->buffer, var->len, &var->y);
	c = var->str[var->i];
	while (var->str[var->i] == c)
		var->buffer[var->y++] = var->str[var->i++];
	new_token(head, var->buffer, var->len, &var->y);
	escape_space(var->str, &var->i, 0);
	if (!var->str[var->i])
		return (0);
	token_sep(var->str, &var->i, &var->sep, &var->var);
	if (var->str[var->i] == ';' || var->str[var->i] == '<'
		|| var->str[var->i] == '>' || var->str[var->i] == '|')
	{
		if (var->sep != 0)
			var->str[var->i] = -var->str[var->i];
		token_type(var, head);
	}
	return (1);
}

int	token_type(t_lexing *var, t_lexer **head)
{
	if ((var->str[var->i] == ' ' && var->sep != 0)
		|| (var->str[var->i] == '~' && var->sep == '"'))
		var->str[var->i] = -var->str[var->i];
	if (var->sep == 0)
	{
		if (((var->str[var->i] == ';' || var->str[var->i] == '<'
					|| var->str[var->i] == '>' || var->str[var->i] == '|')))
		{
			if (extra_token_type(var, head) == 0)
				return (0);
		}
	}
	if (var->str[var->i] == '$')
		var->var = 1;
	return (1);
}
