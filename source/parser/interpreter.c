/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:13:42 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/16 16:13:42 by mbeaujar         ###   ########.fr       */
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
    if(value != NULL)
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
    if(!command->args)
        exit(0);

    while(command->args[i])
    {
        if(command->args[i] == '$')
        {
            start = i;
            while(command->args[i] != ' ' && command->args[i] != '\0') {
                i++;
                pos++;
            }
            i = start; 
            env = search_env(prompt->env, ft_substr(command->args, start + 1, pos - 1));
            command->args = replace_occurence(command->args, ft_substr(command->args, start , pos), env != NULL ? env->value : NULL);
            if(env != NULL)
                i += ft_strlen(env->value);
            else
                i += pos;
        }
        i++;
    }
}

void interpreter(t_prompt *prompt)
{
    t_command *ptr;
    int i;

    ptr = prompt->list;
    while(ptr != NULL)
    {
        i = 0;
        set_env_var(ptr, prompt);
        while(ptr->args[i])
        {
            if(ptr->args[i] < 0)
                ptr->args[i] = -ptr->args[i];
            i++;
        }
        if (ft_strncmp(ptr->args, "echo", 4) == 0)
            echoo(prompt, ft_split(ptr->args, ' '));
        ptr = ptr->next;
    }


    // printlstcommand(prompt->list);
    // if (ft_strncmp(args[0], "ls", 2) == 0)
    //     ls_for_check(prompt, args);
    // if (prompt->setup.debug == 1)
    //     printf("\nla commande : '%s'\n", cmd);
    // if (args[1])
    //     debug(prompt, args, search);
    // if (ft_strncmp(args[0], "exit", 4) == 0)
    //     exitt(prompt, args);
    // if (ft_strncmp(args[0], "env", 3) == 0)
    //     env(prompt, args);
    // if (ft_strncmp(args[0], "export", 6) == 0)
    //     export(prompt, args);
    // if (ft_strncmp(args[0], "cd", 2) == 0)
    //     cd(prompt, args);
    // if (ft_strncmp(args[0], "history", 7) == 0)
    //     printlstbuffer(prompt->buffer);
    // if (ft_strncmp(args[0], "unset", 5) == 0)
    //     unset(prompt, args);
    // if (ft_strncmp(args[0], "pwd", 3) == 0)
    //     pwd(prompt);
    
}