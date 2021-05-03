/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 14:17:37 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/03 17:45:29 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *return_env_name(char *env)
{
	int		i;
	char	*name;

	i = 0;
	while (env[i] != '=')
		i++;
	if (!(name = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (env[i] != '=')
	{
		name[i] = env[i];
		i++;
	}
	name[i] = 0;
	return (name);
}

char *return_env_value(char *env)
{
	int		i;
	char	*value;
	
	i = 0;
	while (*env && *env != '=')
		env++;
	if (!(value = malloc(sizeof(char) * ((int)ft_strlen(++env) + 1))))
		return (NULL);
	while (*env != 0)
	{
		value[i] = *env;
		i++;
		env++;
	}
	value[i] = 0;
	return (value);
}

int is_value(char *env)
{
	while (*env)
	{
		if (*env == '=')
			return (1);
		env++;
	}
	return (0);
}