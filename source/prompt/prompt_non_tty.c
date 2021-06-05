/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_non_tty.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 17:19:23 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/05 21:24:43 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_tty(t_prompt *prompt, int state)
{
	if (state == 0)
		secure_free(prompt->line);
	freelstenv(&prompt->env);
	close(0);
	close(1);
	close(2);
	exit(0);
}

void	sighandler(int sig)
{
	if (sig == SIGINT)
		printf("\n");
}

void	prompt_non_tty(t_prompt *prompt)
{
	int		ret;
	char	*line;

	errno = 0;
	line = NULL;
	ret = 1;
	prompt->indice = 1;
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	while (ret)
	{
		ret = get_next_line(0, &line);
		prompt->line = line;
		if (ret == 0)
			exit_tty(prompt, 0);
		if (ret == -1)
		{
			printerrno_fd(1);
			exit_tty(prompt, 1);
		}
		cmd(prompt, line);
		free(line);
		prompt->line = NULL;
		prompt->indice++;
	}
}
