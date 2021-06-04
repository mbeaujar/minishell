/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 14:28:30 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/04 14:33:54 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** exit affiche exit et quitte (valeur du exit == unsigned char)
**
** affiche tout le temps exit meme dans l'erreur
**
** exit 5y      -- exit -- bash: exit: 5y: numeric argument required -- $? == 2
** exit 257     -- exit -- $? == 1
** exit 5 6     -- bash: exit: too many arguments
*/

int	valid_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i + 1] && i == 0 && (arg[i] == '-' || arg[i] == '+'))
			i++;
		if (arg[i] < '0' || arg[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

unsigned char	mini_atoi(char *arg)
{
	unsigned char	nb;
	int				i;
	int				sign;

	nb = 0;
	i = 0;
	sign = 1;
	if (arg[i] == '-' || arg[i] == '+')
	{
		if (arg[i] == '-')
			sign = -1;
		i++;
	}
	while (arg[i] >= '0' && arg[i] <= '9')
		nb = (nb * 10) + (arg[i++] - 48);
	return (nb * sign);
}

void	free_all(t_prompt *prompt, char **args, unsigned char returned)
{
	(void)args;
	g_buffer(FREE, NULL);
	secure_free(prompt->cmd);
	freelstenv(&prompt->env);
	freelstlexer(&prompt->lexer);
	freelstcommand(&prompt->list);
	freelstbuffer(&prompt->buffer);
	if (prompt->isatty == 1)
		disablerawmode(prompt->orig_termios);
	close(2);
	close(1);
	close(0);
	exit(returned);
}

void	exitt(t_prompt *prompt, char **args)
{
	int				len;
	unsigned char	nb;
	char			*ret;

	len = ft_strlen_tab(args);
	nb = 0;
	prompt->returned = 1;
	if (len == 1)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		free_all(prompt, args, 0);
	}
	if (len > 2 && valid_arg(args[1]))
		return ((void)printf("exit\nbash: exit: too many arguments\n"));
	ret = check_args(args, valid_arg);
	if (ret != NULL)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_putstr_fd("bash: exit: ", STDOUT_FILENO);
		ft_putstr_fd(ret, STDOUT_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDOUT_FILENO);
		free_all(prompt, args, 2);
	}
	ft_putstr_fd("exit\n", 1);
	free_all(prompt, args, mini_atoi(args[1]));
}
