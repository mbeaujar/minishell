/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atinseau <atinseau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 12:02:07 by atinseau          #+#    #+#             */
/*   Updated: 2021/05/03 12:09:53 by atinseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Determine les parametres du programme minishell
 *  --debug | affiche l'historique des commandes 
 * 
 **/
void setup(t_prompt *prompt, int argc, char **argv)
{
    int i;
    (void)prompt;
    
    i = 0;
    if(argc != 1)
    {
        i++;
        while(i < argc) {
            if(ft_strncmp("--debug", argv[i], 7) == 0)
            {
                prompt->setup.debug = 1;
            }
            i++;
        }
    }
}



