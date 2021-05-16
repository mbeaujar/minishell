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

void interpreter(t_prompt *prompt) {

     printlstcommand(prompt->list);
    
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
    if (ft_strncmp(prompt->list->args[0], "echo", 4) == 0)
        echoo(prompt, prompt->list->args);

}