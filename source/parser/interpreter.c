/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:13:42 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/22 00:36:55 by mbeaujar         ###   ########.fr       */
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
    return (args);
}

void exec_command(t_prompt *prompt, t_command **ptr, char **args)
{
    (*ptr)->argv = args;
    if ((*ptr)->key == PIP)
    {
        (*ptr)->next->argv = space_to_neg_tab(prompt, (*ptr)->next);
        if (is_valid_command(prompt, (*ptr), args) && is_valid_command(prompt, (*ptr)->next, (*ptr)->next->argv))
        {
            exec_pipe(prompt, (*ptr), (*ptr)->next);
            (*ptr) = (*ptr)->next->next;
        }
    }
    else
    {
        if (is_valid_command(prompt, (*ptr), args))
        {
            redir((*ptr));
            which_command(prompt, (*ptr), args);
            close_redir((*ptr));
        }
    }
}

void interpreter(t_prompt *prompt)
{
    t_command *ptr;
    char **args;

    ptr = prompt->list;
    while (ptr != NULL)
    {
        if (ptr->argv)
            free(ptr->argv);
        args = space_to_neg_tab(prompt, ptr);
        if (args)
        {
            exec_command(prompt, &ptr, args);
            free(args);
        }
        if (ptr)
            ptr = ptr->next;
    }
}