/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:44:48 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/21 14:45:03 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *replace_occurence(char *src, char *key, char *value)
{
    char *new;
    char *coord;

    new = NULL;
    coord = ft_strnstr(src, key, ft_strlen(src));
    ft_unleak_strjoin(&new, ft_substr(src, 0, ft_strlen(src) - ft_strlen(coord)));
    if (value != NULL)
        ft_unleak_strjoin(&new, value);
    ft_unleak_strjoin(&new, ft_substr(coord, ft_strlen(key), ft_strlen(coord) - ft_strlen(key)));

    free(src);
    return (new);
}

void set_env_var(t_command *command, t_prompt *prompt)
{
    t_env *env;
    int i;
    int start;
    int pos;

    (void)prompt;

    i = 0;
    start = 0;
    pos = 0;
    env = NULL;
    if (!command->args)
        exit(0);

    while (command->args[i])
    {
        if (command->args[i] == '$')
        {
            start = i;
            while (command->args[i] != ' ' && command->args[i] != '\0' && command->args[i] > 0)
            {
                i++;
                pos++;
            }
            i = start;
            env = search_env(prompt->env, ft_substr(command->args, start + 1, pos - 1));
            command->args = replace_occurence(command->args, ft_substr(command->args, start, pos), env != NULL ? env->value : NULL);
            if (env != NULL)
                i += ft_strlen(env->value);
            else
                i += pos;
        }
        i++;
    }
}