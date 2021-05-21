/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:45:17 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/22 00:36:19 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **recup_path(t_prompt *prompt)
{
    t_env *find;
    char **path;

    path = NULL;
    find = search_env(prompt->env, "PATH");
    if (!find || !find->value)
        return (NULL);
    path = ft_split(find->value, ':');
    return (path);
}

int is_builtin(char **args)
{
    if (!ft_strcmp(args[0], "echo") || !ft_strcmp(args[0], "cd"))
        return (1);
    if (!ft_strcmp(args[0], "export") || !ft_strcmp(args[0], "env"))
        return (1);
    if (!ft_strcmp(args[0], "exit") || !ft_strcmp(args[0], "pwd"))
        return (1);
    if (!ft_strcmp(args[0], "unset"))
        return (1);
    return (0);
}

int is_path_relative(t_command *list, char **args)
{
    int len;
    struct stat file;

    len = (int)ft_strlen(args[0]);
    if (len > 2 && args[0][0] == '.' && args[0][1] == '/')
    {
        if (stat(args[0], &file) != -1)
        {
            list->path = ft_strdup(args[0]);
            return (1);
        }
    }
    printf("bash: %s : command not found\n", args[0]);
    return (0);
}

int is_valid_command(t_prompt *prompt, t_command *list, char **args)
{
    struct stat file;
    char **path;
    int i;

    if (!args)
        return (0);
    if (is_builtin(args))
        return (1);
    i = 0;
    path = recup_path(prompt);
    if (!path)
        return (!printf("bash: %s : command not found\n", args[0]));
    while (path[i])
    {
        path[i] = ft_strjoin_gnl(path[i], "/");
        path[i] = ft_strjoin_gnl(path[i], args[0]);
        if (stat(path[i], &file) != -1)
        {
            list->path = ft_strdup(path[i]);
            free_tab(path);
            return (1);
        }
        i++;
    }
    free_tab(path);
    return (is_path_relative(list, args));
}

void    which_command(t_prompt *prompt, t_command *ptr, char **args)
{
    if (ft_strcmp(args[0], "echo") == 0)
        echoo(prompt, args);
    else if (ft_strcmp(args[0], "cd") == 0)
        cd(prompt, args);
    else if (ft_strcmp(args[0], "export") == 0)
        export(prompt, args);
    else if (ft_strcmp(args[0], "env") == 0)
        env(prompt, args);
    else if (ft_strcmp(args[0], "exit") == 0)
        exitt(prompt, args);
    else if (ft_strcmp(args[0], "pwd") == 0)
        pwd(prompt, args);
    else if (ft_strcmp(args[0], "unset") == 0)
        unset(prompt, args);
    else 
        unbuiltin(prompt, ptr, args);
}