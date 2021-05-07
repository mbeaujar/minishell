/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthurtinseau <arthurtinseau@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 14:28:28 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/07 20:41:33 by arthurtinse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// go faire un printf
// echo -n , print nothing
// echo , print \n
// echo -n salut, print salut et \n

void echoo(t_prompt *prompt, char **args)
{
    int line_return;
    int i;
    int args_len;

    line_return = 1;
    args_len = ft_strlen_tab(args);
    i = 0;
    if(strncmp("echo", args[0], 4) == 0) {

        if(args_len > 1) {
              
            if(args[1][0] == '-' && args[1][1] == 'n' && ft_strlen(args[1]) == 2) {
                line_return = 0;
                i++;
            }
            i++;

            while(i < ft_strlen_tab(args)) {
                ft_putstr_fd(args[i], 1);
                i++;
            }
        }

        if(line_return == 1)
            ft_putchar_fd('\n', 1);

        prompt->returned = 0;
    }
}