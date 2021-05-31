/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:13:32 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/31 17:05:49 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_command *newlstcommand(char *args)
{
    t_command *new;


    if (!(new = malloc(sizeof(t_command) * 1)))
        return (NULL);
    new->args = args;
    new->code_errno = 0 ;
    new->path_file = NULL;
    new->std_in = STDIN_FILENO;
    new->std_out = STDOUT_FILENO;
    new->key = DEFAULT;
    new->next = NULL;
    new->path = NULL;
    new->argv = NULL;
    new->previous = NULL;
    return (new);
}

void lstaddbackcommand(t_command **list, t_command *new)
{
    t_command *ptr;

    if(!*list) {
        *list = new;
        return;
    }

    ptr = *list;
    while(ptr->next != NULL)
        ptr = ptr->next;
    ptr->next = new;
    new->previous = ptr;

    // *list = ptr;
}

void freelstcommand(t_command **list)
{
    t_command *tmp;

    if (!list || !(*list))
        return;
    while((*list)->previous != NULL)
        *list = (*list)->previous;
    while((*list) != NULL)
    {
        tmp = *list;
        *list = (*list)->next;
        if (tmp->args)
            free(tmp->args);
        if (tmp->argv)
            free_tab(tmp->argv);
        if (tmp->path)
            free(tmp->path);
        if (tmp->std_in != 0)
            close(tmp->std_in);
        if (tmp->std_out != 1)
            close(tmp->std_out);
        free(tmp);
        tmp = NULL;
    }
}