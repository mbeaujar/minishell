/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:51:42 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/01 18:04:15 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printerrno_fd(int fd)
{
	char	*ret_error;

	ret_error = strerror(errno);
	ft_putstr_fd(ret_error, fd);
	ft_putchar_fd('\n', 1);
}

void	cmd(t_prompt *prompt, char *str)
{
	char	*cmd;

	cmd = ft_secure_strdup(str);
	if (!cmd)
		return ;
	prompt->lexer = lexer(prompt, cmd);
	if (prompt->lexer == NULL)
	{
		free(cmd);
		return ;
	}
	prompt->list = parse(prompt->lexer);
	if (prompt->isatty == 1)
		disablerawmode(prompt->orig_termios);
	interpreter(prompt);
	if (prompt->isatty == 1)
		enablerawmode(prompt->raw);
	freelstlexer(&prompt->lexer);
	freelstcommand(&prompt->list);
	free(cmd);
}
