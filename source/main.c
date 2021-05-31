/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 15:10:06 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/31 21:56:57 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_prompt(t_prompt *prompt)
{
	prompt->buffer = NULL;
	prompt->indice = 0;
	prompt->env = NULL;
	prompt->returned = 0;
	prompt->list = NULL;
	prompt->lexer = NULL;
	prompt->isatty = 0;
}

int main(int argc, char **argv, char **envp)
{
	t_prompt prompt;
	int ret;
	errno = 0;
	(void)ret;

	init_prompt(&prompt);
	setup(&prompt, argc, argv);
	prompt.env = fill_env(envp, &prompt);
	if (prompt.setup.debug == 1)
		printlstenv(prompt.env);
	find_env_shlvl(&prompt);
	find_env_path(&prompt);

	// isatty -- check si le fd link à un terminal
	//if (isatty(0))
	//	prompt.isatty = 1;

	if (prompt.isatty)
	{

		ret = tcgetattr(STDIN_FILENO, &prompt.orig_termios);
		if (ret == -1)
		{
			printerrno_fd(1);
			return (ret);
		}
		prompt.raw = prompt.orig_termios;
		ret = init_termcaps();
		if (ret == -1)
		{
			printerrno_fd(1);
			return (ret);
		}
		enablerawmode(prompt.raw);

		read_stdin(&prompt);
		g_buffer(FREE, NULL);
		freelstbuffer(&prompt.buffer);
		disablerawmode(prompt.orig_termios);
	}
	else
		prompt_tty(&prompt);
	return (0);
}