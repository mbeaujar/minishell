/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atinseau <atinseau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 15:10:06 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/03 12:06:49 by atinseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	init_termcaps();
	enablerawmode(prompt.raw);
    // refill env
	read_stdin(&prompt);
    if (prompt.modified)
        g_buffer(FREE, NULL);
    freelstbuffer(&prompt.buffer);
	disablerawmode(prompt.orig_termios);
	return (0);
}