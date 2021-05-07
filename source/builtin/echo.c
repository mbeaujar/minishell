/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthurtinseau <arthurtinseau@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 14:28:28 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/07 20:15:44 by arthurtinse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// go faire un printf

void echo(t_prompt *prompt, char **args)
{
    char c; 
    
    c = 0;
    if(prompt->setup.interprete_isspace == 1)
        c = '\n';
    ft_printf("%s%c", *args, c);
    prompt->returned = 0;
}