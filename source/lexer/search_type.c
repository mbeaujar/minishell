/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 02:24:43 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/14 19:59:17 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** ERROR : 
**
** echo salut < < file1     --- bash: syntax error near unexpected token `<'
** echo salut | |           --- bash: syntax error near unexpected token `|'
** ls ; ;                   --- bash: syntax error near unexpected token `;'
** ; ls                     --- bash: syntax error near unexpected token `;'
** | ls                     --- bash: syntax error near unexpected token `|'
** ls |                     --- Error multiline
** ls >                     --- bash: syntax error near unexpected token `newline'
** ls <                     --- bash: syntax error near unexpected token `newline'
*/

int count_redir(char *str, char redir)
{
    int count;

    count = 0;
    while (str[i] == )
}

int check_token(t_lexer *head)
{
    while (head)
    {
        
    } 
}

