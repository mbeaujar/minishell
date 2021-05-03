/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 15:10:06 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/03 20:16:48 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


/*
** free before exit 
**
**   freelstenv
**   freelstbuffer
**   disablerawmode
*/

void link_terminal(void)
{
	int i;

	i = 0;
	while (i < 3)
	{
		errno = 0;
		if (!(isatty(i)))
		{
			// printerrno_fd(????);
			exit(i);
		}
		i++;
	}
}

int main(int argc, char **argv, char **envp)
{
	t_prompt prompt;
	(void)argc;
	(void)argv;
    (void)envp;
	// check PATH si elle existe 
	// si non alors chercher le chemin dans /etc/environment

	//settings minishell
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
    if (prompt.modified)
        g_buffer(FREE, NULL);
    freelstbuffer(&prompt.buffer);
	disablerawmode(prompt.orig_termios);
	return (0);
}