/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:45:17 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/21 18:50:08 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_valid_command(t_command *list, t_prompt *prompt, int state)
{
    char **args;
    char **paths;
    t_env *env;
    struct stat file;
    int i;
    char *path;

    args = ft_split(list->args, ' ');
    if (args == NULL)
        return (0);
    if (!ft_strcmp(args[0], "echo") || !ft_strcmp(args[0], "cd") || !ft_strcmp(args[0], "export") || !ft_strcmp(args[0], "env") || !ft_strcmp(args[0], "exit") || !ft_strcmp(args[0], "pwd") || !ft_strcmp(args[0], "unset"))
    {
        free_tab(args);
        return (1);
    }
    env = search_env(prompt->env, "PATH");
    paths = NULL;
    if (env != NULL)
        paths = ft_split(env->value, ':');
    i = 0;
    path = NULL;
    while (paths[i])
    {
        path = ft_strdup(paths[i]);
        ft_argv_strjoin(&path, 2, "/", args[0]);
        if (stat(path, &file) != -1)
        {
            free(path);
            free_tab(args);
            return (1);
        }
        free(path);
        i++;
    }
    if (state == 1)
        printf("bash: %s : command not found\n", args[0]);
    free_tab(args);
    free_tab(paths);
    return (0);
}

void unbuiltin(t_prompt *prompt, char **args)
{
    char **paths;
    t_env *env;
    struct stat file;
    int status;
    int i;
    char *path;

    env = search_env(prompt->env, "PATH");
    paths = NULL;
    if (env != NULL)
        paths = ft_split(env->value, ':');
    i = 0;
    path = NULL;
    while (paths[i])
    {
        path = ft_strdup(paths[i]);
        ft_argv_strjoin(&path, 2, "/", args[0]);
        if (stat(path, &file) != -1)
        {
            errno = 0;
            i = -1;
            i = fork();
            if (i == 0)
            {
                //printf("'%s'\n", path);
                if (execve(path, args++, new_table_env(prompt->env)) == -1)
                {
                    printerrno_fd(1);
                    kill(i, 0);
                    exit(0);
                }
            }
            free(path);
            waitpid(i, &status, 0);
            return;
        }
        free(path);
        i++;
    }
}

builtin_func which_command(char **args)
{
    if (ft_strcmp(args[0], "echo") == 0)
        return (echoo);
    if (ft_strcmp(args[0], "cd") == 0)
        return (cd);
    if (ft_strcmp(args[0], "export") == 0)
        return (export);
    if (ft_strcmp(args[0], "env") == 0)
        return (env);
    if (ft_strcmp(args[0], "exit") == 0)
        return (exitt);
    if (ft_strcmp(args[0], "pwd") == 0)
        return (pwd);
    if (ft_strcmp(args[0], "unset") == 0)
        return (unset);
    return (unbuiltin);
}