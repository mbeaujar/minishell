/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_createenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 16:22:36 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/02 16:26:24 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** crée une variable non définie
*/

void ft_createenv(t_prompt *prompt, char *s1, char *s2)
{
    char *env;
    int len_s1;

    len_s1 = (int)ft_strlen(s1);
    if (!(env = malloc(sizeof(char) *  (len_s1 + (int)ft_strlen(s2) + 1))))
        return ;
    ft_strlcpy(env, s1, len_s1);
    ft_strjoin(env, s2);
    free(s2);
    addlstenv(&prompt->env, env);
}