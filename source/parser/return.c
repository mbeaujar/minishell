/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 15:08:24 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/30 15:41:12 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void secure_free(char *str)
{
    if (str)
        free(str);
}

int is_return_var(char *str, int i)
{
    if (str[i] == '$' && str[i + 1] && str[i + 1] == '?' && !is_endvar(str[i + 2]))
        return (1);
    return (0);
}

char *add_value_return_var(t_prompt *prompt, char *str, int i)
{
    char *prev;
    int len_str;
    char *ret;
    char *next;

    next = NULL;
    ret = NULL;
    len_str = (int)ft_strlen(str);
    if (str[i + 2] != 0)
        next = ft_substr(str, i + 2, len_str - i);
    prev = ft_substr(str, 0, i);
    ret = ft_itoa(prompt->returned);
    ft_unleak_strjoin(&prev, ret);
    secure_free(ret);
    ft_unleak_strjoin(&prev, next);
    secure_free(next);
    secure_free(str);
    return (prev);
}