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

void printerrno_fd(int fd)
{
    char *ret_error;

    ret_error = strerror(errno);
    ft_putstr_fd(ret_error, fd);
    ft_putchar_fd('\n', 1);
    return;
}

/*
**  bash-4.4# ls ; echo salut < file1 ; ls
**  bin  boot  dev  etc  home  lib  lib64  media  mnt  opt  proc  root  run  sbin  srv  sys  tmp  usr  var
**  bash: file1: No such file or directory
**  bin  boot  dev  etc  home  lib  lib64  media  mnt  opt  proc  root  run  sbin  srv  sys  tmp  usr  var
*/

void cmd(t_prompt *prompt, char *str)
{
    char *cmd;

    cmd = ft_secure_strdup(str);
    if (!cmd)
        return ;
    prompt->lexer = lexer(prompt, cmd);
    if (prompt->lexer == NULL)
    {
        free(cmd);
        return ;
    }
    prompt->list = parse(prompt->lexer);
    // check si il y a un fd à -1 (message d'erreur + $?)
    if (prompt->isatty == 1)
        disablerawmode(prompt->orig_termios);
    interpreter(prompt);
    if (prompt->isatty == 1)
        enablerawmode(prompt->raw);
    freelstlexer(&prompt->lexer);
    freelstcommand(&prompt->list);
    free(cmd);
}