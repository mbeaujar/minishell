/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 14:28:25 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/03 21:51:58 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

    (void)prompt;
    //refresh_oldpwd();
    refresh_pwd(prompt, "OLDPWD");
    if ((ret = chdir(path)) == -1)
        return (printerrno_fd(0));
    //refresh_pwd();
    refresh_pwd(prompt, "PWD");
}

void cd(t_prompt *prompt, char *args)
{
    int i;

    i = 0;
    while (args[i] && args[i] != ' ')
        i++;
    while (args[i] && args[i] == ' ')
        i++;
    if (prompt->setup.debug)
        printf("cd : '%s'\n", args + i);
    change_directory(prompt, args + i);
}