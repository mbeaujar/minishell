/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 19:29:51 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/01 18:20:43 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_shlvl(char *old_arg)
{
	int		i;
	char	*arg;

	i = 0;
	arg = ft_strtrim(old_arg, " ");
	while (arg[i])
	{
		if (i == 0 && (arg[i] == '+' || arg[i] == '-'))
			i++;
		if (arg[i] < '0' || arg[i] > '9')
		{
			free(arg);
			return (0);
		}
		i++;
	}
	free(arg);
	return (1);
}

size_t	recup_shlvl(char *str)
{
	size_t	nb;
	size_t	i;
	size_t	sign;

	nb = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		nb = (nb * 10) + (str[i++] - '0');
	free(str);
	if ((int)(nb * sign) < 0)
		return (0);
	if ((int)++nb > 998)
	{
		printf("bash: warning: shell level (");
		printf("%zu) too high, resetting to 1\n", nb);
		nb = 1;
	}
	return (nb);
}

void	find_env_shlvl(t_prompt *prompt)
{
	t_env	*find;
	size_t	nb;

	find = search_env(prompt->env, "SHLVL");
	if (!find)
		addlstenv(&prompt->env, ft_create_env("SHLVL", "1", FREE_NOT));
	else if (!find->value)
		find->value = ft_strdup("1");
	else if (valid_shlvl(find->value) == 0)
	{
		free(find->value);
		find->value = ft_strdup("1");
	}
	else
	{
		nb = recup_shlvl(ft_strtrim(find->value, " "));
		free(find->value);
		find->value = ft_itoa((int)nb);
	}
}
