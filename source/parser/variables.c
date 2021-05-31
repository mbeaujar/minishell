/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:44:48 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/31 16:15:27 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *replace_env_to_value(char *src, char *key, t_env *env)
{
    char *new;
    char *coord;
    char *value;
    char *tmp;
    int len_key;
    int len_src;
    int len_coord;

    new = NULL;
    value = NULL;
    if (env)
        value = env->value;
    len_src = (int)ft_strlen(src);
    len_key = (int)ft_strlen(key);
    coord = ft_strnstr(src, key, len_src);
    len_coord = (int)ft_strlen(coord);
    tmp = ft_substr(src, 0, len_src - len_coord);
    ft_unleak_strjoin(&new, tmp);
    secure_free(tmp);
    ft_unleak_strjoin(&new, value);
    tmp = ft_substr(coord, len_key, len_coord - len_key);
    ft_unleak_strjoin(&new, tmp);
    secure_free(tmp);
    secure_free(src);
    return (new);
}

int is_endvar(char c)
{
    return (c != ' ' && c != 0 && c > 0);
}

void search_len(t_command *ptr, int *i, int *len, int *start)
{
    (*start) = (*i);
    while (is_endvar(ptr->args[(*i)]))
    {
        (*i)++;
        (*len)++;
        if (ptr->args[(*i)] == '$')
            break;
    }
    (*i) = (*start);
}

void normi_variable(t_prompt *prompt, t_command *ptr, int i)
{
    if (is_return_var(ptr->args, i))
        ptr->args = add_value_return_var(prompt, ptr->args, i);
    if (ptr->args[i] == '~' && (ptr->args[i + 1] == '/' || !is_endvar(ptr->args[i + 1])))
        ptr->args = add_tildes_var(prompt, ptr->args, i);
}

void search_variable(t_command *ptr, t_prompt *prompt)
{
    t_env *env;
    char *tmp;
    int i;
    int start;
    int len;

    i = 0;
    while (ptr->args[i++])
    {
        len = 0;
        normi_variable(prompt, ptr, i);
        if (ptr->args[i] == '$' && is_endvar(ptr->args[i + 1]))
        {
            search_len(ptr, &i, &len, &start);
            tmp = ft_substr(ptr->args, start + 1, len - 1);
            env = search_env(prompt->env, tmp);
            secure_free(tmp);
            tmp = ft_substr(ptr->args, start, len);
            ptr->args = replace_env_to_value(ptr->args, tmp, env);
            secure_free(tmp);
            if (env != NULL)
                i += ft_strlen(env->value);
            i--;
        }
    }
}