/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 15:52:12 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/05 13:04:44 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_env(t_env *head)
{
	while (head)
	{
		if (head->value != NULL)
		{
			ft_putstr_fd(head->name, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putstr_fd(head->value, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		head = head->next;
	}
}

void	arguments_env(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

char	*check_args(char **args, int (*fct)())
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (fct(args[i]) == 0)
			return (args[i]);
		i++;
	}
	return (NULL);
}

void	env(t_prompt *prompt, char **args)
{
	int		len;
	char	*ret;

	len = ft_strlen_tab(args);
	if (len == 1)
	{
		display_env(prompt->env);
		prompt->returned = 0;
		return ;
	}
	ret = check_args(args, is_value);
	if (ret != NULL)
	{
		ft_putstr_fd("env: '", STDOUT_FILENO);
		ft_putstr_fd(ret, STDOUT_FILENO);
		ft_putstr_fd("': No such file or directory\n", STDOUT_FILENO);
		prompt->returned = 127;
		return ;
	}
	display_env(prompt->env);
	arguments_env(args);
}
