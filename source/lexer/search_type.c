/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 02:24:43 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/25 00:25:03 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** ERROR : 
**
** echo salut < < file1     --- bash: syntax error near unexpected token `<'
** echo salut | |           --- bash: syntax error near unexpected token `|'
** ls ; ;                   --- bash: syntax error near unexpected token `;'
** ; ls                     --- bash: syntax error near unexpected token `;'
** | ls                     --- bash: syntax error near unexpected token `|'
** ls |                     --- Error multiline
** ls >                     --- bash: syntax error near unexpected token `newline'
** ls <                     --- bash: syntax error near unexpected token `newline'
** echo  '<<<<<<'  <<<<     --- bash: syntax error near unexpected token `<<'
*/

int endl_sep(type key)
{
    if (key == LEFT || key == RIGHT)
        ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 1);
    if (key == PIP)
        ft_putstr_fd("bash: syntax error multiline\n", STDOUT_FILENO);
    return (0);
}

int double_sep(type key)
{
    ft_putstr_fd("bash: syntax error near unexpected token `", 1);
    if (key == LEFT)
        ft_putchar_fd('<', 1);
    if (key == RIGHT)
        ft_putchar_fd('>', 1);
    if (key == DRIGHT)
        ft_putstr_fd(">>", 1);
    if (key == COMAT)
        ft_putchar_fd(';', 1);
    if (key == PIP)
        ft_putchar_fd('|', 1);
    ft_putstr_fd("'\n", 1);
    return (0);
}

int which_redir(char *str)
{
    if (str[0] == '>' && str[1] == '>')
        return (DRIGHT);
    if (str[0] == '>')
        return (RIGHT);
    return (LEFT);
}

int check_sep_token(t_lexer **head)
{
    if ((*head) && ((*head)->token[0] == '<' || (*head)->token[0] == '>'))
    {
        if (count_redir((*head)->token, (*head)->token[0]) == 0)
            return (0);
        (*head)->key = which_redir((*head)->token);
        printf("key : %d\n", (*head)->key);
        if (!(*head)->next)
            return (endl_sep((*head)->key));          
    }
    else if ((*head) && (*head)->token[0] == ';')
    {
        if (count_comat((*head)->token) == 0)
            return (0);
        (*head)->key = COMAT;
    }
    else if ((*head) && (*head)->token[0] == '|')
    {
        if (count_pip((*head)->token) == 0)
            return (0);
        (*head)->key = PIP;
    }
   else if ((*head)->previous && is_redir((*head)->previous->key))
        (*head)->key = PATH;
    return (1);
}

int check_token(t_lexer *head)
{
    while (head)
    {
        if (check_sep_token(&head) == 0)
            return (0);
        if (head && head->key == COMAT && !head->previous)
            return (double_sep(head->key));
        if (head && (is_redir(head->key) || head->key == PIP) && !head->next)
            return (endl_sep(head->key));
        if (head && head->previous && is_double_sep(head->previous->key, head->key))
            return (double_sep(head->key));
        if (head && head->previous && is_redir(head->key) && is_redir(head->previous->key))
            return (double_sep(head->key));
        if (head)
            head = head->next;
    }
    return (1);
}
