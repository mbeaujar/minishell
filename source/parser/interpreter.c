/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:13:42 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/23 17:59:14 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void redir(t_command *ptr)
{
    int fd_out;
    int fd_in;

    if (ptr->std_out != 1)
    {
        fd_out = dup(1);
        dup2(ptr->std_out, 1);
        close(ptr->std_out);
        ptr->std_out = fd_out;
    }
    if (ptr->std_in != 0)
    {
        fd_in = dup(0);
        dup2(ptr->std_in, 0);
        close(ptr->std_in);
        ptr->std_in = fd_in;
    }
}

void close_redir(t_command *ptr)
{
    if (ptr->std_out != 1)
    {
        dup2(ptr->std_out, 1);
        close(ptr->std_out);
    }
    if (ptr->std_in != 0)
    {
        dup2(ptr->std_in, 0);
        close(ptr->std_in);
    }
}

char **space_to_neg_tab(t_prompt *prompt, t_command *ptr)
{
    char **args;
    int i;
    int e;

    i = 0;
    set_env_var(ptr, prompt);
    args = ft_split(ptr->args, ' ');
    if (!args)
        return (NULL);
    while (args[i] != NULL)
    {
        e = 0;
        while (args[i][e])
        {
            if (args[i][e] < 0)
                args[i][e] = -args[i][e];
            e++;
        }
        i++;
    }
    free(ptr->args);
    ptr->args = NULL;
    return (args);
}

void exec_command(t_prompt *prompt, t_command **ptr)
{
    t_command *tmp;

    if ((*ptr)->key == PIP)
    {
        tmp = (*ptr);
        while (tmp && tmp->key == PIP)
        {
            if (!tmp->argv)
                tmp->argv = space_to_neg_tab(prompt, tmp);
            if (!is_valid_command(prompt, tmp, tmp->argv))
                return;
            tmp = tmp->next;
        }
        if (!tmp->argv)
            tmp->argv = space_to_neg_tab(prompt, tmp);
        if (!is_valid_command(prompt, tmp, tmp->argv))
            return;
        build_pipe(prompt, *ptr);
        //exec_pipe(prompt, *ptr, (*ptr)->next);
        *ptr = tmp->next;
    }
    else
    {
        if (is_valid_command(prompt, (*ptr), (*ptr)->argv))
        {
            redir((*ptr));
            which_command(prompt, (*ptr), (*ptr)->argv);
            close_redir((*ptr));
        }
    }
}

void interpreter(t_prompt *prompt)
{
    t_command *ptr;

    ptr = prompt->list;
    while (ptr != NULL)
    {
        ptr->argv = space_to_neg_tab(prompt, ptr);
        if (ptr->argv)
        {
            exec_command(prompt, &ptr);
        }
        if (ptr)
            ptr = ptr->next;
    }
}