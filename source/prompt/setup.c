/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 12:02:07 by atinseau          #+#    #+#             */
/*   Updated: 2021/05/03 21:19:49 by mbeaujar         ###   ########.fr       */
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
    
    i = 1;
    prompt->setup.debug = 0;
    if (argc != 1)
    {
        while (i < argc)
        {
            if (ft_strncmp("--debug", argv[i], 8) == 0)
            {
                prompt->setup.debug = 1;
            }
            i++;
        }
    }
}



