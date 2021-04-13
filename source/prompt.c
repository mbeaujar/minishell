/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:40:30 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/04/13 18:20:25 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void display_prompt(void)
{
	ft_putstr_fd("minishell $> ", 0);
}

void prompt(void)
{
	int ret;
	char *str;

	ret = 1;
	str = NULL;
	while (ret)
	{
		display_prompt();
		ret = get_next_line(0, &str);
		if (ret == -1)
		{
			// Tout free avant l'exit
			exit(1);
		}
		if (ret == 0)
		{
			// Tout free avant l'exit
			ft_putstr_fd("exit\n", 0);
			exit(2);
		}
		printf("'%s'\n", str);
		free(str);
	}
}
