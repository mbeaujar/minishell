/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 14:28:28 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/11 18:34:24 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// go faire un printf
// echo -n , print nothing
// echo , print \n
// echo -n salut, print salut et \n
// echo je suis la, print les agrs avec un espace entre chaque

void echoo(t_prompt *prompt, char **args)
{
    int line_return;
    int i;
    int args_len;

    line_return = 0;
    args_len = ft_strlen_tab(args);
    i = 1;
    if (args_len > 1)
    {
        if (args[1][0] == '-' && args[1][1] == 'n' && ft_strlen(args[i]) == 2)
            line_return = i++;
        while (args[i])
        {
            ft_putstr_fd(args[i], prompt->list->std_out);
            if (args[i + 1])
                ft_putchar_fd(' ', prompt->list->std_out);
            i++;
        }
    }
    if (line_return == 0)
        ft_putchar_fd('\n', prompt->list->std_out);
    prompt->returned = 0;
}