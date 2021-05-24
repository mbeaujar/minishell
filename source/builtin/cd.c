/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 14:28:25 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/25 01:08:33 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** cd ~         -- le tildes "~" est interpété au niveau du parsing
** cd           -- cd $HOME
** cd /         -- fonctionne de base
** cd .. toto   -- bash: cd: too many arguments
*/

void refresh_pwd(t_prompt *prompt, char *name)
{
    t_env *search;
    char *cwd;
    errno = 0;

    if (!(cwd = malloc(sizeof(char) * (PATH_MAX + 1))))
        return ;
    if (getcwd(cwd, PATH_MAX))
    {
        cwd = ft_realloc(cwd);
        if (!(search = search_env(prompt->env, name)))
            addlstenv(&prompt->env, ft_create_env(name, cwd, FREE_S2));
        else
        {
            if (search->value != NULL)
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
    int ret;
    errno = 0;
    
    refresh_pwd(prompt, "OLDPWD");
    if ((ret = chdir(path)) == -1)
    {
        prompt->returned = 1;
        return (printerrno_fd(1));
    }
    refresh_pwd(prompt, "PWD");
    prompt->returned = 0;
}

void cd(t_prompt *prompt, char **args)
{
    int len;
    t_env *find;

    prompt->returned = 0;
    len = ft_strlen_tab(args);
    find = NULL;
    if (len == 1)
    {
        find = search_env(prompt->env, "HOME");
        if (!find)
        {
            ft_putstr_fd("bash: cd: HOME: No such file or directory", STDOUT_FILENO);
            prompt->returned = 1;
        }
        else
            change_directory(prompt, find->value);
        return ;
    }
    if (len > 2)
    {
        prompt->returned = 1;
        ft_putstr_fd("bash: cd: too many arguments\n", STDOUT_FILENO);
        return ;
    }
    if (prompt->setup.debug)
        printf("cd : '%s'\n", args[1]);
    change_directory(prompt, args[1]);
}