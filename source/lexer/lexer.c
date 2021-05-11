/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 16:34:11 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/11 18:09:05 by mbeaujar         ###   ########.fr       */
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
        if (str[i] == ' ' && i == 0)
        {
            while (str[i] && str[i] == ' ')
                i++;
        }
        //printf("c : %c     sep : %d   i : %d\n", str[i], sep, i);
        if (i > 0 && sep == str[i] && str[i - 1] != '\\')
        {
            //printf("del sep : %c i : %d\n", sep, i);
            sep = 0;
            //if (str[i + 1])
            i++;
        }
        if (i == 0 && ((sep == 0 && str[i] == '"') || (sep == 0 && str[i] == '\'')))
        {
            sep = str[i];
            if (!str[i + 1])
                i--;
            i++;
        }
        if ((sep == 0 && str[i] == '"' && str[i - 1] != '\\') || (sep == 0 && str[i] == '\'' && str[i - 1] != '\\'))
        {
            sep = str[i];
            if (!str[i + 1])
                i--; // error nombre de quotes impair
            i++;
            //printf("add sep : %c i : %d\n", sep, i);
        }
        if (sep != '\'' && str[i] == '\\')
        {
            //printf("before -- sep : %d i : %d c : %c\n", sep, i, str[i]);
            if (str[i + 1])
                str[i + 1] = -str[i + 1];
            if (sep == 0 && str[i + 1])
                i++;
            //printf("after -- sep : %d i : %d c : %c\n", sep, i, str[i]);
        }
        if ((str[i] == ' ' && sep == 0))
        {
            buffer[y] = 0;
            while (str[i] && str[i] == ' ')
                i++;
            //printf("buffer : '%s'\n", buffer);
            lstaddbacklexer(head, newlstlexer(ft_strdup(buffer)));
            ft_bzero(buffer, len);
            y = 0;
            if (!str[i])
                break;
        }
        else if (sep != str[i])
        {
            //printf("c : %c      sep : %d\n", str[i], sep);
            buffer[y] = str[i];
            y++;
            i++;
        }
        if (!str[i])
        {
            buffer[y] = 0;
            //printf("buffer : '%s'\n", buffer);
            lstaddbacklexer(head, newlstlexer(ft_strdup(buffer)));
            ft_bzero(buffer, len);
        }
    }
    if (sep != 0)
    {
        free(buffer);
        printf("error\n");
        return;
    }
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

/* int main(void)
{
    char str[] = "ls";
    t_lexer *head = lexer(str);
    printlstlexer(head);
    freelstlexer(&head);
    return (0);
} */