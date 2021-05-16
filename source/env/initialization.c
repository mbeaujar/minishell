/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 17:50:00 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/15 19:30:03 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**  check si PATH existe 
**  si non alors chercher le chemin dans /etc/environment
**
** root@d431c8d2bd41:/# unset PATH
** root@d431c8d2bd41:/# bash --posix
** bash: bash: No such file or directory
*/

/*
** root@d431c8d2bd41:/# unset TERM
** root@d431c8d2bd41:/# bash --posix                                                                     
** bash: bash: No such file or directory
*/

/*
** check si SHLVL existe
** si non alors la set à 1
*/

/*
** mettre l'index de la variable _ à -2
*/

void find_env_path(t_prompt *prompt)
{
    t_env *find;

    find = search_env(prompt->env, "PATH");
    if (PATH)
}
