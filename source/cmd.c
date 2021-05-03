/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atinseau <atinseau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 15:50:37 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/03 12:14:07 by atinseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** affiche le message d'errno
*/

void printerrno_fd(int fd)
{
    char *ret_error;

    ret_error = strerror(errno);
    ft_putendl_fd(ret_error, fd);
    return ;
}

/*
** chaque commande envoyé dans le prompt arrive ici 
** cmd est une copie avec strdup 
*/

void cmd(t_prompt *prompt, char *cmd)
{
    (void)prompt;
    printf("\nla commande : '%s'\n", cmd);
    free(cmd);
}