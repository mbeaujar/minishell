/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 16:09:32 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/30 15:39:39 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void pwd(t_prompt *prompt, char **args)
{
    char *cwd;

    (void)args;
    if (!(cwd = malloc(sizeof(char) * (PATH_MAX + 1))))
        return ;
    if (getcwd(cwd, PATH_MAX))
    {
        prompt->returned = 0;
        ft_putstr_fd(cwd, STDOUT_FILENO);
        ft_putchar_fd('\n', STDOUT_FILENO);
        free(cwd);
    }
    else
    {
        prompt->returned = 1;
        free(cwd);
        printerrno_fd(STDOUT_FILENO);
    }
}