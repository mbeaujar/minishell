/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 19:29:51 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/15 19:31:29 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int valid_shlvl(char *arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        if (i == 0 && (arg[i] == '+' || arg[i] == '-'))
            i++;
        if (arg[i] < '0' || arg[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

/*
** si mauvaise caractère --- 1
** si en dessous de 0 --- 0 
** sinon -- SHLVL + 1
*/

void find_env_shlvl(t_prompt *prompt)
{
    t_env *find;
    int nb;

    find = search_env(prompt->env, "SHLVL");
    if (!find)
        addlstenv(&prompt->env, ft_create_env("SHLVL", "1", FREE_NOT));
    else if (!find->value)
        find->value = ft_strdup("1");
    else if (valid_shlvl(find->value) == 0)
    {
        free(find->value);
        find->value = ft_strdup("1");
    }
    else
    {
        
    }
}
