/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthurtinseau <arthurtinseau@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 15:50:37 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/07 20:17:19 by arthurtinse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** fonction pour debug cd
** fonction type pour les commandes non builtin
*/

void signhandler(int signal)
{
    printf("oui\n");
    if (signal)
    {
        if (errno != 0)
            printerrno_fd(STDOUT_FILENO);
    }
    exit(0);
}

void ls_for_check(t_prompt *prompt, char **args)
{
    //char **args;
    int pid;
    char **envp;

    envp = new_table_env(prompt->env);
    if (prompt->setup.debug == 1)
        printf("%s\n", args[1]);
    errno = 0;
    pid = -1;
    pid = fork();
    if (pid == 0)
    {
        //signal(SIGTERM, signhandler);
        if (execve("/bin/ls", args, envp) == -1)
            printerrno_fd(STDIN_FILENO);
        printf("je suis la\n");
        exit(0);
    }
    wait(&pid);
    //free(args[1]);
    //free(args);
    free_tab(envp);
}

/*
** affiche le message d'errno
*/

void printerrno_fd(int fd)
{
    char *ret_error;

    ret_error = strerror(errno);
    ft_putendl_fd(ret_error, fd);
    return;
}

/*
** chaque commande envoyé dans le prompt arrive ici 
** cmd est une copie avec strdup 
*/

void debug(t_prompt *prompt, char **cmd, t_env *search)
{
    if (*cmd[1] && ft_strncmp(cmd[1], "$OLDPWD", 7) == 0)
    {
        search = search_env(prompt->env, "OLDPWD");
        if (search)
            printf("name : '%s' value : '%s'\n", search->name, search->value);
        else
            printf("NULL\n");
    }
    if (ft_strncmp(cmd[1], "$PWD", 4) == 0)
    {
        search = search_env(prompt->env, "PWD");
        if (search)
            printf("name : '%s' value : '%s'\n", search->name, search->value);
        else
            printf("NULL\n");
    }
    if (ft_strncmp(cmd[1], "$?", 2) == 0)
    {
        printf("%d\n", prompt->returned);
    }
    if (ft_strncmp(cmd[0], "ls", 2) == 0)
        ls_for_check(prompt, cmd);
}

void cmd(t_prompt *prompt, char *cmd)
{
    t_env *search;
    char **args;

    search = NULL;
    args = ft_split(cmd, ' ');
    /*     args = malloc(sizeof(char*) * 2);
    if (!args)
        return ;
    args[0] = cmd;
    args[1] = 0; */
    if (prompt->setup.debug == 1)
        printf("\nla commande : '%s'\n", cmd);
    // debug(prompt, args, search);
    if (ft_strncmp(args[0], "exit", 4) == 0)
        exitt(prompt, args);
    if (ft_strncmp(args[0], "env", 3) == 0)
        env(prompt, args);
    if (ft_strncmp(args[0], "export", 6) == 0)
        export(prompt, args);
    if (ft_strncmp(cmd, "cd", 2) == 0)
        cd(prompt, args);
    if (ft_strncmp(cmd, "history", 7) == 0)
        printlstbuffer(prompt->buffer);
    if (ft_strncmp(cmd, "unset", 5) == 0)
        unset(prompt, cmd);
    if (ft_strncmp(cmd, "pwd", 3) == 0)
        pwd();
    free(cmd);
    free_tab(args);
}