/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 15:52:12 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/07 17:08:45 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** env              -- affiche les variables d'environments qui ont une values
** env RA           -- env: 'RA': No such file or directory
** env RO=salut     -- affiche RO dans env mais que temporairement (si on fait env après il disparait) 
** env RO=salut RA  -- env: 'RA': No such file or directory
*/


void display_env(t_env *head)
{
    while (head)
    {
        if (head->value != NULL)
            printf("%s=%s\n", head->name, head->value);
        head = head->next;
    }
}

void arguments_env(char **args)
{
    int i;

    i = 1;
    while (args[i])
    {
        ft_putstr_fd(args[i], STDOUT_FILENO);
        ft_putchar_fd('\n', STDOUT_FILENO);
        i++;
    }
}

char  *check_args(char **args)
{
    int i;

    i = 1;
    while (args[i])
    {
        if (is_value(args[i]) == 0)
            return (args[i]);
        i++;
    }
    return (NULL);
}

void env(t_prompt *prompt, char **args)
{
    int len;
    char *ret;

    //ft_printtab(args);
    len = ft_strlen_tab(args);
    if (len == 1)
        return ;
    if ((ret = check_args(args)) != NULL)
    {
        ft_putstr_fd("env: '", STDOUT_FILENO);
        ft_putstr_fd(ret, STDOUT_FILENO);
        ft_putstr_fd("': No such file or directory\n", STDOUT_FILENO);
        return ;
    }
    display_env(prompt->env);
    arguments_env(args);
}