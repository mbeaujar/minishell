/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 16:40:43 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/23 17:36:12 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
** void example(t_prompt *prompt, t_command *ptr)
** {
**    int status;
**    int cout[2];
**    int pid[2];
**
**    pipe(cout);
**    pid[0] = add_child_process(prompt, ptr, 0, cout[1]);
**    close(cout[1]);
**
**    if (!ptr->next->argv)
**        ptr->next->argv = space_to_neg_tab(prompt, ptr->next);
**    is_valid_command(prompt, ptr->next, ptr->next->argv);
**    pid[1] = add_child_process(prompt, ptr->next, cout[0], 1);
**    close(cout[0]);
**
**    waitpid(pid[0], &status, 0);
**    waitpid(pid[1], &status, 0);
** } 
*/

int nbpipe(t_command *ptr)
{
    int i;

    i = 0;
    if (!ptr)
        return (i);
    while (ptr && ptr->key == PIP)
    {
        ptr = ptr->next;
        i++;
    }
    return (i + 1);
}