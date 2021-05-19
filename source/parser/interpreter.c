/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:13:42 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/19 20:44:39 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char *pathbin_command(char *searched, t_prompt *prompt)
// {

// }

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

void pipe_fd(t_command *list, int *tmp_in, int *tmp_out)
{
    int fd[2];
    (void)fd;
    // fd [0] = lecture
    // fd [1] = écriture
    pipe(fd);
    // pipe donne 2 fd connectés

    *tmp_out = dup(1);
    *tmp_in = dup(0);

    /*     dup2(list->std_out, *tmp_out);
    dup2(list->next->std_in, *tmp_in); */
    

    list->std_out = fd[1];
    list->next->std_in = fd[0];
}

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
                dup2(prompt->list->std_out, STDOUT_FILENO);
                dup2(prompt->list->std_in, STDIN_FILENO);
                if (execve(path, args++, new_table_env(prompt->env)) == -1)
                {
                    ft_printf("%s", strerror(errno));
                    exit(0);
                }
            }
            free(path);
            wait(&i);
            return;
        }
        free(path);
        i++;
    }
}

builtin_func which_command(char **args)
{
    if (ft_strcmp(args[0], "echo") == 0)
        return echoo;
    if (ft_strcmp(args[0], "cd") == 0)
        return cd;
    if (ft_strcmp(args[0], "export") == 0)
        return export;
    if (ft_strcmp(args[0], "env") == 0)
        return env;
    if (ft_strcmp(args[0], "exit") == 0)
        return exitt;
    if (ft_strcmp(args[0], "pwd") == 0)
        return pwd;
    if (ft_strcmp(args[0], "unset") == 0)
        return unset;

    return unbuiltin;
}

void interpreter(t_prompt *prompt)
{
    t_command *ptr;
    char **args;
    int i;
    // char *path;
    int fd[2];
    (void)fd;
    ptr = prompt->list;
    while (ptr != NULL)
    {
        i = 0;
        set_env_var(ptr, prompt);
        while (ptr->args[i])
        {
            if (ptr->args[i] < 0)
                ptr->args[i] = -ptr->args[i];
            i++;
        }
        args = ft_split(ptr->args, ' ');

        if (ptr->key == PIP)
        {
            if (is_valid_command(ptr, prompt, 1) && is_valid_command(ptr->next, prompt, 0))
            {

               // pipe_fd(ptr, &fd[0], &fd[1]);

                // ft_printf("%d, %d\n", ptr->std_out, ptr->next->std_in);

                // exit(0);

                which_command(args)(prompt, args);

                // printf("pip oui\n");
            }
        }
        else
        {
            if (is_valid_command(ptr, prompt, 1))
            {
                /*if(ptr->previous && ptr->previous->key == PIP)
                {
                    dup2(fd[0], 1);
                } */
                //ft_printf("no pip command\n");
                which_command(args)(prompt, args);
                /*if (ptr->previous && ptr->previous->key == PIP)
                {
                    dup2(fd[0], 0);
                   // dup2(fd[1], 1);
                } */
                //   if(ptr->previous != NULL && ptr->previous->key == PIP)
                //     close(ptr->previous->std_out);
            }
        }

        ptr = ptr->next;
    }
}