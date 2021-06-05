/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 15:10:06 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/04 15:44:06 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_prompt(t_prompt *prompt)
{
	prompt->buffer = NULL;
	prompt->indice = 0;
	prompt->env = NULL;
	prompt->returned = 0;
	prompt->list = NULL;
	prompt->lexer = NULL;
	prompt->isatty = 0;
	prompt->pid = NULL;
	prompt->std = NULL;
	prompt->line = NULL;
	prompt->cmd = NULL;
}

int	prompt_tty(t_prompt *prompt)
{
	int	ret;

	ret = tcgetattr(STDIN_FILENO, &prompt->orig_termios);
	if (ret == -1)
	{
		printerrno_fd(1);
		return (ret);
	}
	prompt->raw = prompt->orig_termios;
	ret = init_termcaps();
	if (ret == -1)
	{
		printerrno_fd(1);
		return (ret);
	}
	enablerawmode(prompt->raw);
	read_stdin(prompt);
	g_buffer(FREE, NULL);
	freelstbuffer(&prompt->buffer);
	disablerawmode(prompt->orig_termios);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_prompt	prompt;

	errno = 0;
	init_prompt(&prompt);
	setup(&prompt, argc, argv);
	if (isatty(0) && prompt.setup.debug == 0)
		prompt.isatty = 1;
	prompt.env = fill_env(envp);
	find_env_shlvl(&prompt);
	find_env_path(&prompt);
	if (prompt.isatty)
		return (prompt_tty(&prompt));
	else
		prompt_non_tty(&prompt);
	return (0);
}
