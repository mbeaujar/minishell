/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 16:24:11 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/15 18:20:58 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_redir(char *str, char redir)
{
    int i;

    i = 0;
    while (str[i] && str[i] == redir)
        i++;
    if (i > 1)
    {
        ft_putstr_fd("bash: syntax error near unexpected token `", 1);
        ft_putchar_fd(redir, 1);
        ft_putstr_fd("'\n", 1);
        return (0);
    }
    if (str[i])
    {
        printf("problem lexer 1\n");
        return (0);
    }
    return (1);
}

int count_comat(char *str)
{
    int i;
    
    i = 0;
    while (str[i] && str[i] == ';')
        i++;
    if (i > 1)
    {
        printf("bash: syntax error near unexpected token `;;'\n");
        return (0);
    }
    if (str[i])
    {
        printf("problem lexer 2\n");
        return (0);
    }
    return (1);
}

int count_pip(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] == '|')
        i++;
    if (i > 1)
    {
        printf("bash: syntax error near unexpected token `|'\n");
        return (0);
    }
    if (str[i])
    {
        printf("problem lexer 3\n");
        return (0);
    }
    return (1);
}


int is_redir(type key)
{
    if (key == LEFT || key == RIGHT)
        return (1);
    return (0);
}

/*
** ; <
** ; >
** | <
** | >
*/

int is_double_sep(type key1, type key2)
{
    if (key1 == PATH || key2 == PATH)
        return (0);
    if (key1 == DEFAULT || key2 == DEFAULT)
        return (0);
    if (key1 == COMAT && is_redir(key2))
        return (0);
    if (key1 == PIP && is_redir(key2))
        return (0);
    return (1);
}