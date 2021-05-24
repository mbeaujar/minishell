/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:55:34 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/25 00:25:26 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Si stdout de la première commande ou stdin de la 2ème est redirigé alors ne pas modifié
**
** echo salut > test | cat
** écris salut dans test et n'affiche rien
**
** echo salut | cat < Makefile
** affiche Makefile dans le term
**
** echo salut | cat | cat 
** affiche salut
**
** echo salut | cat | cat | echo 
** affiche un retour à la ligne
**
** echo salut | cat | echo | cat
** affiche un retour à la ligne
*/

/*
** fd[0] = lecture
** fd[1] = écriture
**
** valgrind --track-fds=yes
*/

/*
** Première fonction de test
*/

int nbpipe(t_command *ptr)
{
    int i;

    i = 0;
    if (!ptr)
        return (i);
    while (ptr && ptr->key == PIP)
    {
        ptr = ptr->next;
        i++;
    }
    return (i + 1);
}