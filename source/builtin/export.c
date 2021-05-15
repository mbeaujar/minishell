/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 14:28:32 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/14 18:16:07 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** export           -- affiche env trié par ordre ascii sauf l'env _ 
** export RA        -- ajoute RA sans values
** export RO=       -- ajoute RO=""
** export RI=""     -- ajoute RI=""
** export RE=''     -- ajoute RE=""
** export =merci    -- bash: export: `=merci': not a valid identifier   -- $? == 1
** export =         -- bash: export: `=': not a valid identifier        -- $? == 1
** export RA=s =    -- bash: export: `=': not a valid identifier        -- $? == 1
** Si il y a une erreur $? == 1 meme si il y a des variables qui sont set 
** export ro=salut=yo
*/

/*
** export ro:
** export ro+
** export ro^
** export =e
** export $ 
** export var?
** export 1
** export 1=salut
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
    while (index <= index_max)
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

void new_var(t_prompt *prompt, char *args, char *name, char *value)
{
    t_env *find;

    find = NULL;
    find = search_env(prompt->env, name);
    if (find == NULL)
    {
        free(name);
        if (value != NULL)
            free(value);
        addlstenv(&prompt->env, ft_strdup(args));
    }
    else if (value != NULL)
    {
        if (find->value != NULL)
            free(find->value);
        find->value = value;
        free(name);
    }
}

void export_var(t_prompt *prompt, char **args)
{
    int i;
    char *name;
    char *value;

    i = 1;
    name = NULL;
    value = NULL;
    while (args[i])
    {
        name = return_env_name(args[i]);
        if (is_value(args[i]))
            value = return_env_value(args[i]);
        if (args[i][0] == '=' || is_valid_identifier(name) == 0)
        {
            ft_putstr_fd("bash: export: `", STDOUT_FILENO);
            ft_putstr_fd(args[i], STDOUT_FILENO);
            ft_putstr_fd("': not a valid identifier\n", STDOUT_FILENO);
            free(name);
            if (value)
                free(value);
            prompt->returned = 1;
        }
        else if (name != NULL && name[0] != 0)
            new_var(prompt, args[i], name, value);
        i++;
    }
}

void export(t_prompt *prompt, char **args)
{
    int len;

    len = ft_strlen_tab(args);
    prompt->returned = 0;
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