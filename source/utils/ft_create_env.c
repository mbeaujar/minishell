/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 16:22:36 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/03 19:28:58 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** crée une variable non définie
** state = FREE_S1 FREE_S2 FREE_ALL FREE_NO
*/

char *ft_create_env(char *s1, char *s2, int state)
{
    char *env;
    
    env = ft_strjoin_env(s1, s2);
    if (state == FREE_S1 || state == FREE_ALL)
        free(s1);
    if (state == FREE_S2 || state == FREE_ALL)
        free(s2);
    return (env);
}