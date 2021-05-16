/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_secure_strdup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:13:22 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/16 16:17:16 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int strlen_dup(const char *str)
{
    int i;
    int len;

    i = 0;
    len = 0;
     while(str[i])
    {
        if(str[i] > 0)
            len++;
        i++;
    }
    return (len);
}

char *ft_secure_strdup(const char *str)
{
    int i;
    int len;
    char *new;

    if(!str || str[0] == 0)
        return (NULL);
    if((new = malloc(sizeof(char) * (strlen_dup(str) + 1))) == NULL)
        return (NULL);
    i = 0;
    len = 0;
    while(str[i])
    {
        if(str[i] > 0)
        {
            new[len] = str[i];
            len++;
        }
        i++;
    }
    new[len] = '\0';
    return (new);
}