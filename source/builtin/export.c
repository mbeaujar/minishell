/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 14:28:32 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/04 19:21:29 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_export(t_env *head)
{
	t_env	*find;
	int		index;

	index = 0;
	while (is_indexable(head))
	{
		find = search_min(head);
		find->index = index;
		index++;
	}
}

void	display_export(t_env *head)
{
	int		index;
	int		index_max;
	t_env	*tmp;

	index = 0;
	index_max = max_index(head);
	while (index <= index_max)
	{
		tmp = search_index(head, index);
		if (tmp != NULL && head->index != -2)
		{
			ft_putstr_fd("export ", STDOUT_FILENO);
			ft_putstr_fd(tmp->name, STDOUT_FILENO);
			if (tmp->value != NULL)
			{
				ft_putstr_fd("=\"", STDOUT_FILENO);
				ft_putstr_fd(tmp->value, STDOUT_FILENO);
				ft_putchar_fd('"', STDOUT_FILENO);
			}
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		index++;
	}
}

void	new_var(t_prompt *prompt, char *args, char *name, char *value)
{
	t_env	*find;

	find = search_env(prompt->env, name);
	if (!find)
	{
		secure_free(name);
		secure_free(value);
		addlstenv(&prompt->env, args);
	}
	else if (find && value)
	{
		secure_free(find->value);
		find->value = value;
		secure_free(name);
	}
	else
		secure_free(name);
}

void	export_var(t_prompt *prompt, char **args)
{
	int		i;
	char	*name;
	char	*value;

	i = 1;
	name = NULL;
	value = NULL;
	while (args[i])
	{
		name = return_env_name(args[i]);
		if (name && is_value(args[i]))
			value = return_env_value(args[i]);
		if (name && (args[i][0] == '=' || is_valid_identifier(name) == 0))
		{
			printf("bash: export: `%s': not a valid identifier\n", args[i]);
			secure_free(name);
			secure_free(value);
			prompt->returned = 1;
		}
		else if (name && name[0] != 0)
			new_var(prompt, args[i], name, value);
		i++;
	}
}

void	export(t_prompt *prompt, char **args)
{
	int	len;

	len = ft_strlen_tab(args);
	prompt->returned = 0;
	if (len == 1)
	{
		if (is_indexable(prompt->env))
		{
			clear_index(prompt->env);
			sort_export(prompt->env);
		}
		display_export(prompt->env);
		return ;
	}
	else
		export_var(prompt, args);
}
