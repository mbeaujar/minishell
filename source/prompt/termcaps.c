/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:11:10 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/02 15:12:03 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int init_termcaps(void)
{
	int ret;
	char *term_type;

	term_type = "xterm-256color";
	if (!term_type)
	{
		ft_putstr_fd("TERM must be set (see 'env').\n", 0);
		return (-1);
	}
	ret = tgetent(NULL, term_type);
	if (ret == -1)
	{
		ft_putstr_fd("Could not acces to the termcap database.\n", 0);
		return (-1);
	}
	else if (ret == 0)
	{
		ft_putstr_fd("Terminal type '%s' is not defined in termcap database.\n", 0);
		return (-1);
	}
	return (0);
}

int display_termcap(int c)
{
	char cast;

	cast = (char)c;
	return (write(1, &cast, 1));
}

void create_termcap(char *termcap)
{
	char *new_termcap;

	new_termcap = tgetstr(termcap, NULL);
	tputs(new_termcap, 1, display_termcap);
	//free(new_termcap);
}