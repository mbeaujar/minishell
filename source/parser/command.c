/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:45:17 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/02 22:26:43 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**recup_path(t_prompt *prompt)
{
	t_env	*find;
	char	**path;

	path = NULL;
	find = search_env(prompt->env, "PATH");
	if (!find || !find->value)
		return (NULL);
	path = ft_split(find->value, ':');
	return (path);
}

int	is_builtin(char **args)
{
	if (!ft_strcmp(args[0], "echo") || !ft_strcmp(args[0], "cd"))
		return (1);
	if (!ft_strcmp(args[0], "export") || !ft_strcmp(args[0], "env"))
		return (1);
	if (!ft_strcmp(args[0], "exit") || !ft_strcmp(args[0], "pwd"))
		return (1);
	if (!ft_strcmp(args[0], "unset"))
		return (1);
	return (0);
}

int	is_path_relative(t_prompt *prompt, t_cmd *list, char **args)
{
	int			len;
	struct stat	file;

	len = (int)ft_strlen(args[0]);
	if ((len > 2 && args[0][0] == '.' && args[0][1] == '/')
		|| (args[0][0] == '/'))
	{
		if (stat(args[0], &file) != -1)
		{
			list->path = ft_strdup(args[0]);
			prompt->returned = 0;
			return (1);
		}
	}
	return (command_not_found(prompt, args));
}

int	check_fd(t_prompt *prompt, t_cmd *ptr)
{
	if (ptr->std_out != -1 && ptr->std_in != -1)
		return (0);
	if (ptr->std_in != -1 && ptr->std_in != 0)
	{
		close(ptr->std_in);
		ptr->std_in = 0;
	}
	if (ptr->std_out != -1 && ptr->std_out != 1)
	{
		close(ptr->std_out);
		ptr->std_out = 1;
	}
	ft_putstr_fd("bash: ", 1);
	ft_putstr_fd(ptr->path_file, 1);
	ft_putstr_fd(": ", 1);
	errno = ptr->code_errno;
	printerrno_fd(1);
	prompt->returned = 1;
	errno = 0;
	return (1);
}

int	is_valid_command(t_prompt *prompt, t_cmd *list, char **args)
{
	struct stat	file;
	char		**path;
	int			i;

	if (!args || check_fd(prompt, list))
		return (0);
	if (is_builtin(args))
		return (1);
	i = 0;
	prompt->returned = 0;
	path = recup_path(prompt);
	if (!path)
		return (command_not_found(prompt, args));
	while (path[i])
	{
		path[i] = ft_strjoin_gnl(ft_strjoin_gnl(path[i], "/"), args[0]);
		if (stat(path[i], &file) != -1)
		{
			list->path = ft_strdup(path[i]);
			return (free_tab(path) + 1);
		}
		i++;
	}
	free_tab(path);
	return (is_path_relative(prompt, list, args));
}
