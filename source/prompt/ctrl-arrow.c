/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl-arrow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 13:49:37 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/06 13:55:00 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void    is_ctrl_arrow(t_prompt *prompt)
{
    char seq[6];
    int i;

    i = 0;
    while (i < 6 && read(0, &seq[i], 1) != 1)
        i++;
    printf("seq : %s\n", seq);    
}

/*
void    search_word(t_prompt *prompt)
{
    
}*/