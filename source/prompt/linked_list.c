/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 19:04:55 by beaujardmae       #+#    #+#             */
/*   Updated: 2021/04/30 20:15:33 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_buffer *newlstbuffer(char *buff)
{
    t_buffer *new;

    if (!(new = malloc(sizeof(t_buffer) * 1)))
        return (NULL);
    new->buff = buff;
    new->buff[0] = 0;
    new->len = 10;
    new->modified = 0;
    new->strlen = 0;
    new->previous = NULL;
    new->next = NULL;
    return (new);    
}

void lstaddfrontbuffer(t_buffer **head, t_buffer *new)
{
    t_buffer *tmp;
    
    if (!*head)
    {
        *head = new;
        return;
    }
    tmp = *head;
    while (tmp->previous)
        tmp = tmp->previous;
    tmp->previous = new;
    new->next = tmp;
    *head = new;
}

void printbuffer(char *str)
{
    if (!str)
        return ;
    while (*str)
    {
        if (*str > 0)
            ft_putchar_fd(*str, STDIN_FILENO);
        str++;
    }
}

void printlstbuffer(t_buffer *head)
{
    int i;

    i = 0;
    if (!head)
        return ;
    while (head->next)
        head = head->next;
    while (head)
    {
        ft_putstr_fd("\t", STDIN_FILENO);
        ft_putnbr_fd(i, STDIN_FILENO);
        ft_putstr_fd("\t", STDIN_FILENO);
        printbuffer(head->buff);
        ft_putchar_fd('\n', STDIN_FILENO);
        i++;
        head = head->previous;
    }
}

void freelstbuffer(t_buffer **begin)
{
    t_buffer *tmp;
    t_buffer *head;

    head = *begin;
    while (head->previous)
        head = head->previous;
    while (head)
    {
        tmp = head;
        head = head->next;
        free(tmp->buff);
        free(tmp);
    }
    *begin = NULL;
}