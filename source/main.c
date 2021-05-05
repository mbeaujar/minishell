/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 15:10:06 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/05 17:10:04 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


/*
** tildes est interpréter que seul ou au début d'un chemin relatif
**
**  ~ 		-- valide
**  ~/..  	-- valide
**  ./~/.   -- non valide
*/


/*
** free before exit 
**
**   freelstenv
**   freelstbuffer
**   disablerawmode
*/

void init_prompt(t_prompt *prompt)
{
	prompt->buffer = NULL;
	prompt->indice = 0;
	prompt->env = NULL;
	prompt->returned = 0;
}

int main(int argc, char **argv, char **envp)
{
	t_prompt prompt;

	//settings minishell
	init_prompt(&prompt);
	setup(&prompt, argc, argv);

	// isatty -- check si le fd link à un terminal 

	tcgetattr(STDIN_FILENO, &prompt.orig_termios);
	// check error tcgetattr
	prompt.raw = prompt.orig_termios;
	
	if ((init_termcaps()) == -1)
		return (3);
	enablerawmode(prompt.raw);

	prompt.env = fill_env(envp, &prompt);	
	// recup les env 

	// check PATH si elle existe 
	// si non alors chercher le chemin dans /etc/environment


	read_stdin(&prompt);
    g_buffer(FREE, NULL);
    freelstbuffer(&prompt.buffer);
	disablerawmode(prompt.orig_termios);
	return (0);
}