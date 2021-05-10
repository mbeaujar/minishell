/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 16:34:11 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/10 18:10:07 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void create_token(t_lexer **head, char *str)
{
    char sep;
    char *buffer;
    int len;
    int i;
    int y;

    i = 0;
    sep = 0;
    y = 0;
    len = (int)ft_strlen(str);
    buffer = malloc(sizeof(char) * (len + 1));
    if (!buffer)
        return;
    while (str[i])
    {
        if (i > 0 && sep == str[i] && str[i - 1] != '\\')
        {
            //printf("del sep : %c i : %d\n", sep, i);
            sep = 0;
            if (str[i + 1])
                i++;
        }
        else if (i == 0 && ((sep == 0 && str[i] == '"') || (sep == 0 && str[i] == '\'')))
            sep = str[i];
        else if ((sep == 0 && str[i] == '"' && str[i - 1] != '\\') || (sep == 0 && str[i] == '\'' && str[i - 1] != '\\'))
        {
            sep = str[i];
            if (str[i + 1])
                i++;
            //printf("add sep : %c i : %d\n", sep, i);
        }
        if ((str[i] == ' ' && sep == 0) || str[i+ 1] == 0)
        {
            buffer[y] = 0;
            lstaddbacklexer(head, newlstlexer(ft_strdup(buffer)));
            ft_bzero(buffer, len);
            y = 0;
        }
        else
        {
            buffer[y] = str[i];
            y++;
        }
        i++;
    }
    if (sep != 0)
    {
        free(buffer);
        printf("error\n");
        return ;
    }
/*     buffer[y] = 0;
    lstaddbacklexer(head, newlstlexer(ft_strdup(buffer))); */
    free(buffer);
}

/*
** str -> liste chainée de token
*/

t_lexer *lexer(char *str)
{
    t_lexer *head;

    head = NULL;
    create_token(&head, str);
    return (head);
}

int main(void)
{
    char str[] = "ls bon\" jour\" \"'je suis la''oui'\" \"moi    aussi\"";
    t_lexer *head = lexer(str);
    printlstlexer(head);
    freelstlexer(&head);
    return (0);
}