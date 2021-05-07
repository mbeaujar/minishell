/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 14:28:32 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/07 18:58:57 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** export           -- affiche env trié par ordre ascii sauf l'env _ 
** export RA        -- ajoute RA sans values
** export RO=       -- ajoute RO=""
** export RI=""     -- ajoute RI=""
** export RE=''     -- ajoute RE=""
*/

void sort_export(t_env *head)
{
    t_env *find;
    int index;

    index = 0;
    while (is_indexable(head))
    {
        find = search_min(head);
        find->index = index;
        index++;
    }
}

t_env *search_index(t_env *head, int index)
{
    while (head)
    {
        if (head->index == index)
            return (head);
        head = head->next;
    }
    return (NULL);
}

void display_export(t_env *head)
{
    int index;
    int index_max;
    t_env *tmp;

    index = 0;
    index_max = max_index(head);
    while (index < index_max)
    {
        tmp = search_index(head, index);
        if (tmp != NULL && head->index != -2)
        {
            ft_putstr_fd("export ", STDOUT_FILENO);
            ft_putstr_fd(tmp->name, STDOUT_FILENO);
            if (tmp->value != NULL)
            {
                ft_putstr_fd("=\"", STDOUT_FILENO);
                ft_putstr_fd(tmp->value, STDOUT_FILENO);
                ft_putchar_fd('"', STDOUT_FILENO);
            }
            ft_putchar_fd('\n', STDOUT_FILENO);
        }
        index++;
    }
}

void export_var(t_prompt *prompt, char **args)
{
    int i;

    i = 1;
    while (args[i])
    {
        addlstenv(&prompt->env, ft_strdup(args[i]));
        i++;
    }
}

void export(t_prompt *prompt, char **args)
{
    int len;

    len = ft_strlen_tab(args);
    if (len == 1)
    {
        if (is_indexable(prompt->env))
        {
            clear_index(prompt->env);
            sort_export(prompt->env);
        }
        display_export(prompt->env);
        return;
    }
    else
        export_var(prompt, args);
}