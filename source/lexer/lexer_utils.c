/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 17:45:45 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/13 18:41:48 by mbeaujar         ###   ########.fr       */
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
    lstaddbacklexer(head, newlstlexer(ft_strdup(buffer)));
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
}

void token_sep(char *str, int *i, char *sep)
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
            (*i)--;
        (*i)++;
    }
    if ((*sep == 0 && str[*i] == '"' && str[*i - 1] != '\\') || (*sep == 0 && str[*i] == '\'' && str[*i - 1] != '\\'))
    {
        *sep = str[*i];
        if (!str[*i + 1])
            (*i)--; // error nombre de quotes impair
        (*i)++;
    }
}

int lexer_error(char sep)
{
    if (sep != 0)
    {
        ft_putstr_fd("Lexer error -- multiline\n", STDOUT_FILENO);
        return (0);
    }
    return (1);
}