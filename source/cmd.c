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

/*
**  bash-4.4# ls ; echo salut < file1 ; ls
**  bin  boot  dev  etc  home  lib  lib64  media  mnt  opt  proc  root  run  sbin  srv  sys  tmp  usr  var
**  bash: file1: No such file or directory
**  bin  boot  dev  etc  home  lib  lib64  media  mnt  opt  proc  root  run  sbin  srv  sys  tmp  usr  var
*/

void cmd(t_prompt *prompt, char *str)
{
    t_lexer *tokens;
    char *cmd;

    cmd = ft_secure_strdup(str);
    if (!cmd)
        return ;
    tokens = lexer(prompt, cmd);
    if (tokens == NULL)
    {
        free(cmd);
        return ;
    }
    prompt->list = parse(tokens);
    // check si il y a un fd à -1 (message d'erreur + $?)
    
    interpreter(prompt);
    freelstlexer(&tokens);
    freelstcommand(&prompt->list);
    free(cmd);
}