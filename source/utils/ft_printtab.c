/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printtab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 16:33:12 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/14 21:04:02 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_printtab(char **args)
{
    int i;

    i = 0;
    while (args[i])
    {
        ft_putstr_fd(args[i++], STDOUT_FILENO);
        ft_putchar_fd(' ', STDOUT_FILENO);
    }
}