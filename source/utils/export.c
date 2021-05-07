/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:44:07 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/07 18:44:46 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_indexable(t_env *head)
{
    while (head)
    {
        if (head->index == -1)
            return (1);
        head = head->next;
    }
    return (0);
}

int max_index(t_env *head)
{
    int index_max;

    index_max = head->index;
    while (head)
    {
        if (index_max < head->index)
            index_max = head->index;
        head = head->next;
    }
    return (index_max);
}

void clear_index(t_env *head)
{
    while (head)
    {
        if (head->index != -2)
            head->index = -1;
        head = head->next;
    }
}