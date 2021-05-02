/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 14:28:25 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/02 16:29:31 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void refresh_pwd(t_prompt *prompt)
{
    t_env *search;
    char *cwd;
    errno = 0;

    if (!(cwd = malloc(sizeof(char) * (PATH_MAX + 1))))
        return ;
    if (getcwd(cwd, PATH_MAX))
    {
        cwd = ft_realloc(cwd);
        if (!(search = search_env(prompt->env, "PWD")))
            ft_createenv(prompt, "PWD=", cwd);
        else
        {
            free(search->value);
            search->value = cwd;
        }
    }
    else
    {
        free(cwd);
        printerrno_fd(STDOUT_FILENO);
    }
}

void change_directory(t_prompt *prompt, char *path)
{
    char *ret_error;
    int ret;
    errno = 0;

    //refresh_oldpwd();
    if ((ret = chdir(path)) == -1)
        return (printerrno_fd(0));
    //refresh_pwd();
    refresh_pwd(prompt);
}

void cd(t_prompt *prompt, char *args)
{
    (void)prompt;
    (void)args;
}