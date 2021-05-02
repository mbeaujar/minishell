/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 15:10:06 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/02 15:15:18 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv)
{
	t_prompt prompt;


	(void)argc;
	(void)argv;
	// check PATH si elle existe 
	// si non alors chercher le chemin dans /etc/environment

	// isatty -- check le fd 
	tcgetattr(STDIN_FILENO, &prompt.orig_termios);
	// check error tcgetattr
	prompt.raw = prompt.orig_termios;

	init_termcaps();
	enablerawmode(prompt.raw);
	read_stdin(&prompt);
	disablerawmode(prompt.orig_termios);
	return (0);
}