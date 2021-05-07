/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_min.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:08:23 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/07 18:08:47 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *search_min(t_env *head)
{
    t_env *find;

    while (head && head->index != -1)
        head = head->next;
    find = head;
    while (head)
    {
        if (head->index == -1 && (ft_strcmp(find->name, head->name)) > 0)
            find = head;
        head = head->next;
    }
    return (find);
}