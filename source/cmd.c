/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 15:50:37 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/07 22:16:24 by mbeaujar         ###   ########.fr       */
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

/*
** ls   -- segfault
** ls . -- valid
*/

void ls_for_check(t_prompt *prompt, char **args)
{
    //char **args;
    int pid;
    char **envp;
    char *empty_args[] = {"ls", ".", NULL};

    envp = new_table_env(prompt->env);
    if (prompt->setup.debug == 1)
        printf("%s\n", args[1]);
    errno = 0;
    pid = -1;
    pid = fork();
    if (pid == 0)
    {
        //signal(SIGTERM, signhandler);
        if (execve("/bin/ls", ft_strlen_tab(args) > 1 ? args : empty_args, envp) == -1)
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
** args est une copie avec strdup 
*/

void debug(t_prompt *prompt, char **args, t_env *search)
{
    if (*args[1] && ft_strncmp(args[1], "$OLDPWD", 7) == 0)
    {
        search = search_env(prompt->env, "OLDPWD");
        if (search)
            printf("name : '%s' value : '%s'\n", search->name, search->value);
        else
            printf("NULL\n");
    }
    if (ft_strncmp(args[1], "$PWD", 4) == 0)
    {
        search = search_env(prompt->env, "PWD");
        if (search)
            printf("name : '%s' value : '%s'\n", search->name, search->value);
        else
            printf("NULL\n");
    }
    if (ft_strncmp(args[1], "$?", 2) == 0)
    {
        printf("%d\n", prompt->returned);
    }
}

void cmd(t_prompt *prompt, char *cmd)
{
    //(void)prompt;
    t_env *search;
    char **args;

    search = NULL;
    args = ft_split(cmd, ' ');
    //printf("%s\n", cmd);
    if (ft_strncmp(args[0], "ls", 2) == 0)
        ls_for_check(prompt, args);
    if (prompt->setup.debug == 1)
        printf("\nla commande : '%s'\n", cmd);
    if (args[1])
        debug(prompt, args, search);
    if (ft_strncmp(args[0], "exit", 4) == 0)
        exitt(prompt, args);
    if (ft_strncmp(args[0], "env", 3) == 0)
        env(prompt, args);
    if (ft_strncmp(args[0], "export", 6) == 0)
        export(prompt, args);
    if (ft_strncmp(args[0], "cd", 2) == 0)
        cd(prompt, args);
    if (ft_strncmp(args[0], "history", 7) == 0)
        printlstbuffer(prompt->buffer);
    if (ft_strncmp(args[0], "unset", 5) == 0)
        unset(prompt, args);
    if (ft_strncmp(args[0], "pwd", 3) == 0)
        pwd(prompt);
    if (ft_strncmp(args[0], "echo", 4) == 0)
        echoo(prompt, args);
    free(cmd);
    free_tab(args);
}