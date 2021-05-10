/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 19:21:58 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/11 00:33:03 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer *newlstlexer(char *token)
{
    t_lexer *new;

    if (!(new = malloc(sizeof(t_lexer) * 1)))
        return (NULL);
    new->token = token;
    new->previous = NULL;
    new->next = NULL;
    return (new);    
}

void lstaddbacklexer(t_lexer **head, t_lexer *new)
{
    t_lexer *tmp;
    
    if (!*head)
    {
        *head = new;
        return;
    }
    tmp = *head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    new->previous = tmp;
    //*head = new;
}

void freelstlexer(t_lexer **begin)
{
    t_lexer *tmp;
    t_lexer *head;

    head = *begin;
    if (!head)
        return ;
    while (head->previous)
        head = head->previous;
    while (head)
    {
        tmp = head;
        head = head->next;
        free(tmp->token);
        free(tmp);
    }
    *begin = NULL;
}

void printlexer(char *str)
{
    if (!str)
        return ;
    while (*str)
    {
        if (*str > 0)
            ft_putchar_fd(*str, STDOUT_FILENO);
        else
            ft_putchar_fd(-(*str), STDOUT_FILENO);
        str++;
    }
}

void printlstlexer(t_lexer *head)
{
    if (!head)
        return ;
    while (head->previous)
        head = head->previous;
    while (head)
    {
        ft_putstr_fd("token : ", 0);
        printlexer(head->token);
        ft_putchar_fd('\n', 0);
        head = head->next;
    }
}