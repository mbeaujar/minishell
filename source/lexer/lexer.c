/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:53:41 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/15 19:04:20 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int token_character(char *str, int *i, char *sep)
{
    escape_space(str, i, 1);
    if (token_sep(str, i, sep) == 0)
        return (0);
    token_backslash(str, i, *sep);
    return (1);
}

int create_token(t_lexer **head, t_lexing *var)
{
    while (var->str[var->i])
    {
        if (token_character(var->str, &var->i, &var->sep) == 0)
            return (lexer_error(var->sep));
       // printf("c : %c     sep : %d\n", var->str[var->i] > 0 ? var->str[var->i] : -var->str[var->i], sep);
        if (token_type(var, head) == 0)
            break;
        if ((var->str[var->i] == ' ' && var->sep == 0))
        {
            escape_space(var->str, &var->i, 0);
            // printf("var->buffer : %s c : %c sep : %d\n", var->buffer, var->str[var->i] > 0 ? var->str[var->i] : -var->str[var->i], sep);
            new_token(head, var->buffer, var->len, &var->y);
            if (!var->str[var->i])
                break;
        }
        else if (var->sep != var->str[var->i])
            var->buffer[var->y++] = var->str[var->i++];
        if (!var->str[var->i])
            new_token(head, var->buffer, var->len, &var->y);
    }
    return (lexer_error(var->sep));
}

/*
** str -> liste chainée de token
*/

void init_struct_lexing(t_lexing *var, char *str)
{
    var->len = (int)ft_strlen(str);
    var->str = str;
    var->y = 0;
    var->buffer = malloc(sizeof(char) * (var->len + 1));
    var->i = 0;
    var->sep = 0;
}

t_lexer *lexer(t_prompt *prompt, char *str)
{
    t_lexer *head;
    t_lexing var;

    head = NULL;
    init_struct_lexing(&var, str);
    if (!var.buffer)
        return (NULL);
    if (create_token(&head, &var) == 0)
    {
        free(var.buffer);
        freelstlexer(&head);
        prompt->returned = 2;
        return (NULL);
    }
    if (check_token(head) == 0)
    {
        free(var.buffer);
        freelstlexer(&head);
        prompt->returned = 2;
        return (NULL);
    }
    free(var.buffer);
    return (head);
}
  
/* int main(void)
{
    //char str[] = "echo salut \"<\" \"|\" | '|' '<<<<<<' <<<<<>file1<file2";
    char str[] = "echo < file1 salut ; < ls > file2 arg1 arg2";
    t_lexer *head = lexer(str);
    if (!head)
        printf("error\n");
    printlstlexer(head);
    freelstlexer(&head);
    return (0);
}   */