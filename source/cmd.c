/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 15:50:37 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/02 15:56:46 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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