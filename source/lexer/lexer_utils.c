/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 17:45:45 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/15 16:19:46 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void escape_space(char *str, int *i, int state)
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

void new_token(t_lexer **head, char *buffer, int len, int *y)
{
    buffer[*y] = 0;
    lstaddbacklexer(head, newlstlexer(ft_strdup(buffer), DEFAULT));
    ft_bzero(buffer, len);
    *y = 0;
}

void token_backslash(char *str, int *i, char sep)
{
    if (sep != '\'' && str[*i] == '\\')
    {
        if (str[*i + 1])
            str[*i + 1] = -str[*i + 1];
        if (sep == 0 && str[*i + 1])
            (*i)++;
        if ((sep == '"' && str[*i + 1] == -34) || (sep == '"' && str[*i + 1] == -92))
            (*i)++;
    }
    if (sep == '\'' && sep != str[*i])
        str[*i] = -str[*i];
    if (sep != 0)
    {
        if (sep == '"' && (str[*i] == '<' || str[*i] == '>' || str[*i] == ';' || str[*i] == '|'))
            str[*i] = -str[*i];
    }
}

int token_sep(char *str, int *i, char *sep)
{
    if ((*i > 0 && *sep == '"' && str[*i] == '"' && str[*i - 1] != '\\') || (*i > 0 && *sep == '\'' && str[*i] == '\''))
    {
        *sep = 0;
        (*i)++;
    }
    if (*i == 0 && ((*sep == 0 && str[*i] == '"') || (*sep == 0 && str[*i] == '\'')))
    {
        *sep = str[*i];
        if (!str[*i + 1])
            return (0);
        (*i)++;
    }
    if ((*sep == 0 && str[*i] == '"' && str[*i - 1] != '\\') || (*sep == 0 && str[*i] == '\'' && str[*i - 1] != '\\'))
    {
        *sep = str[*i];
        if (!str[*i + 1])
            return (0); // error nombre de quotes impair
                        //if (str[*i + 1] != *sep)
        (*i)++;
    }
    return (1);
}

int lexer_error(char sep)
{
    if (sep != 0)
    {
        ft_putstr_fd("bash: syntax error multiline\n", STDOUT_FILENO);
        return (0);
    }
    return (1);
}

int token_type(t_lexing *var, t_lexer **head)
{
    char c;

    c = 0;
    if (var->sep == 0 && ((var->str[var->i] == ';' || var->str[var->i] == '<' || var->str[var->i] == '>' || var->str[var->i] == '|')))
    {
        if (var->buffer[0] != 0)
            new_token(head, var->buffer, var->len, &var->y);
        c = var->str[var->i];
        while (var->str[var->i] == c)
            var->buffer[var->y++] = var->str[var->i++];
        new_token(head, var->buffer, var->len, &var->y);
        escape_space(var->str, &var->i, 0);
        if (!var->str[var->i])
            return (0);
        token_sep(var->str, &var->i, &var->sep);
        if (var->str[var->i] == ';' || var->str[var->i] == '<' || var->str[var->i] == '>' || var->str[var->i] == '|')
        {
            if (var->sep != 0)
                var->str[var->i] = -var->str[var->i];
            token_type(var, head);
        }
    }
    return (1);
}