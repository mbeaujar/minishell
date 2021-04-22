/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:25:55 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/04/15 16:59:06 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	return (name);
}

char *return_env_value(char *env)
{
	int		i;
	char	*value;
	
	i = 0;
	while (*env != '=')
		env++;
	if (!(value = malloc(sizeof(char) * ((int)ft_strlen(++env) + 1))))
		return (NULL);
	while (*env != 0)
	{
		value[i] = *env;
		i++;
		env++;
	}
	return (value);
}