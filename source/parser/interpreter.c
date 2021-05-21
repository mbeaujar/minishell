/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:13:42 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/21 17:08:03 by mbeaujar         ###   ########.fr       */
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

void space_to_neg_tab(char **args)
{
    int i;
    int e;

    i = 0;
    while(args[i] != NULL)
    {
        e = 0;
        while(args[i][e])
        {
            if(args[i][e] < 0)
                args[i][e] = -args[i][e];
            e++;
        }
        i++;
    }
}


void interpreter(t_prompt *prompt)
{
    t_command *ptr;
    char **args;
    int i;
    //int fd[2];
    // fd[0] = lecture
    // fd[1] = écriture
    ptr = prompt->list;
    while (ptr != NULL)
    {
        i = 0;
        set_env_var(ptr, prompt);
        args = ft_split(ptr->args, ' ');
        space_to_neg_tab(args);
        if (ptr->key == PIP)
        {
            if (is_valid_command(ptr, prompt, 1) && is_valid_command(ptr->next, prompt, 0))
            {

                exec_pipe(prompt, ptr, ptr->next, args);
                ptr = ptr->next->next;
                //exit_debug(prompt);
            }
        }
        else
        {
            if (is_valid_command(ptr, prompt, 1))
            {
                redir(ptr);
                which_command(args)(prompt, args);
                close_redir(ptr);
            }
        }
        free(args);
        if (ptr)
            ptr = ptr->next;
    }
}