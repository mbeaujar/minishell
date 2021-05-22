/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 16:40:43 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/22 17:57:39 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void display_all_pipe_fd(int *fd, int len)
{
    for (int i = 0; i < len*2; i++)
    {
        if (i % 2 == 0)
            ft_printf("\tin");
        else
            ft_printf("\tout");
    }
    printf("\n");
    for (int i = 0; i < len*2; i++)
        ft_printf("\t%d", fd[i]);
    printf("\n");
}


int check_command(t_prompt *prompt, t_command *ptr)
{
    if (!ptr->argv)
        ptr->argv = space_to_neg_tab(prompt, ptr);
    if (is_valid_command(prompt, ptr, ptr->argv))
        return (1);
    else
    {
        if (ptr->argv)
        {
            free(ptr->argv);
            ptr->argv = NULL;
        }
        if (ptr->path)
        {
            free(ptr->path);
            ptr->path = NULL;
        }
        return (0);
    }
}

int nbpipe(t_command *ptr, t_prompt *prompt)
{
    int i;

    if (!ptr)
        return (0);
    i = 0;
    while (ptr && ptr->key == PIP)
    {
        if (!check_command(prompt, ptr))
            return (0);
        ptr = ptr->next;
        i++;
    }
    if (!check_command(prompt, ptr))
        return (0);
    return (i + 1);
}