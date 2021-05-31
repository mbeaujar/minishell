/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 15:10:06 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/31 15:55:15 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


/*
** tildes est interpréter que seul ou au début d'un chemin relatif
**
**  ~ 		-- valide
**  ~/..  	-- valide
**  ./~/.   -- non valide 
** ~..		-- non valide	
*/


/*
** free before exit 
**
**   freelstenv
**   freelstbuffer
**   disablerawmode
*/
 
/*
** check les signaux sur un fork
** cmd : 'cat'
** la boucle infinie s'arrete avec ctrl+c ??
*/

void init_prompt(t_prompt *prompt)
{
	prompt->buffer = NULL;
	prompt->indice = 0;
	prompt->env = NULL;
	prompt->returned = 0;
	prompt->list = NULL;
}

int main(int argc, char **argv, char **envp)
{
	t_prompt prompt;
	int ret;
	errno = 0;

	init_prompt(&prompt);
	prompt.envp = envp;
	setup(&prompt, argc, argv);

	// isatty -- check si le fd link à un terminal 

	ret = tcgetattr(STDIN_FILENO, &prompt.orig_termios);
/* 	if (ret == -1)
	{
		printerrno_fd(1);
		return (ret);
	} */
	prompt.raw = prompt.orig_termios;
	ret = init_termcaps();
/* 	if (ret == -1)
	{
		printerrno_fd(1);
		return (ret);
	} */
	enablerawmode(prompt.raw);

	prompt.env = fill_env(envp, &prompt);
	if (prompt.setup.debug == 1)
		printlstenv(prompt.env);
	find_env_shlvl(&prompt);
	find_env_path(&prompt);
	read_stdin(&prompt);
    g_buffer(FREE, NULL);
    freelstbuffer(&prompt.buffer);
	disablerawmode(prompt.orig_termios);
	return (0);
}