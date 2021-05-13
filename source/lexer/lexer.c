/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 16:34:11 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/13 18:59:59 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int create_token(t_lexer **head, char *str, char *buffer, int len)
{
    char sep;
    int i;
    int y;

    i = 0;
    sep = 0;
    y = 0;
    while (str[i])
    {
        escape_space(str, &i, 1);
        token_sep(str, &i, &sep);
        token_backslash(str, &i, sep);
        if ((str[i] == ' ' && sep == 0))
        {
            escape_space(str, &i, 0);
            new_token(head, buffer, len, &y);
            if (!str[i])
                break;
        }
        else if (sep != str[i])
            buffer[y++] = str[i++];
        if (!str[i])
            new_token(head, buffer, len, &y);
    }
    return (lexer_error(sep));
}

/*
** str -> liste chainée de token
*/

t_lexer *lexer(char *str)
{
    t_lexer *head;
    int len;
    char *buffer;

    head = NULL;
    len = (int)ft_strlen(str);
    buffer = malloc(sizeof(char) * (len + 1));
    if (!buffer)
        return (NULL);
    if (create_token(&head, str, buffer, len) == 0)
    {
        free(buffer);
        freelstlexer(&head);
        return (NULL);
    }
    free(buffer);
    return (head);
}

/* int main(void)
{
    char str[] = "echo \"\\\\\"";
    t_lexer *head = lexer(str);
    if (!head)
        printf("error\n");
    printlstlexer(head);
    freelstlexer(&head);
    return (0);
}   */