/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 14:28:35 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/14 16:53:13 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** bash: unset: `ro=salut': not a valid identifier
** bash-4.4# unset :
** bash: unset: `:': not a valid identifier
** bash-4.4# unset %
** bash: unset: `%': not a valid identifier
** bash-4.4# unset ,
** bash: unset: `,': not a valid identifier
** bash-4.4# unset 1
** bash: unset: `1': not a valid identifier
** bash-4.4# unset 2
** bash: unset: `2': not a valid identifier
** bash-4.4# unset RaEZZ
** bash-4.4# 
*/

int is_valid_identifier(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
			i++; 
        else
			return (0);
    }
    return (1);
}

void unset_args(t_prompt *prompt, char **args)
{
	int i;
	t_env *find;

	i = 1;
	while (args[i])
	{
		if (is_valid_identifier(args[i]) == 0)
		{
			ft_putstr_fd("bash: unset: `", STDOUT_FILENO);
			ft_putstr_fd(args[i], STDOUT_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDOUT_FILENO);
			prompt->returned = 1;
		}
		else
		{
			find = search_env(prompt->env, args[i]);
			if (find)
				delete_env(prompt, find);
		}
		i++;
	}
}

void unset(t_prompt *prompt, char **args)
{
	int len;

	len = ft_strlen_tab(args);
	prompt->returned = 0;
	if (len == 1)
		return;
	else
		unset_args(prompt, args);
}