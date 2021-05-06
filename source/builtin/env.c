/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 15:52:12 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/06 20:30:12 by mbeaujar         ###   ########.fr       */
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

void arguments_env(t_prompt *prompt, char *args)
{
    
}

void env(t_prompt *prompt, char **args)
{
    if (ft_strlen_tab(args) == 1)
    {
        return ; 
    }
}