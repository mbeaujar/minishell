/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 21:59:13 by beaujardmae       #+#    #+#             */
/*   Updated: 2021/06/01 20:02:46 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	enablerawmode(struct termios raw)
{
	int	ret;

	raw.c_lflag &= ~ (ECHO | ICANON | IEXTEN | ISIG);
	raw.c_iflag &= ~ (ICRNL | IXON);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
	ret = tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	if (ret == -1)
	{
		printerrno_fd(1);
		exit(ret);
	}
}

void	disablerawmode(struct termios orig_termios)
{
	int	ret;

	errno = 0;
	ret = tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
	if (ret == -1)
		printerrno_fd(1);
}
