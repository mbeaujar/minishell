/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:13:42 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/02 14:48:48 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**space_to_neg_tab(t_prompt *prompt, t_cmd *ptr)
{
	char	**args;
	int		i;
	int		e;

	i = 0;
	search_variable(ptr, prompt);
	args = ft_split(ptr->args, ' ');
	if (!args)
		return (NULL);
	while (args[i] != NULL)
	{
		e = 0;
		while (args[i][e])
		{
			if (args[i][e] < 0)
				args[i][e] = -args[i][e];
			e++;
		}
		i++;
	}
	free(ptr->args);
	ptr->args = NULL;
	return (args);
}

void	exec_command_pipe(t_prompt *prompt, t_cmd **ptr)
{
	t_cmd	*tmp;

	tmp = (*ptr);
	while (tmp && tmp->key == PIP)
	{
		if (!tmp->argv)
			tmp->argv = space_to_neg_tab(prompt, tmp);
		if (!is_valid_command(prompt, tmp, tmp->argv))
			return ;
		tmp = tmp->next;
	}
	if (!tmp->argv)
		tmp->argv = space_to_neg_tab(prompt, tmp);
	if (!is_valid_command(prompt, tmp, tmp->argv))
	{
		*ptr = tmp;
		return ;
	}
	build_pipe(prompt, *ptr);
	*ptr = tmp;
}

void	exec_command(t_prompt *prompt, t_cmd **ptr)
{
	if ((*ptr)->key == PIP)
		exec_command_pipe(prompt, ptr);
	else
	{
		if (!(*ptr)->argv)
			(*ptr)->argv = space_to_neg_tab(prompt, *ptr);
		if (is_valid_command(prompt, (*ptr), (*ptr)->argv))
		{
			redir((*ptr));
			which_command(prompt, (*ptr), (*ptr)->argv);
			close_redir((*ptr));
		}
	}
}

void	interpreter(t_prompt *prompt)
{
	t_cmd	*ptr;

	ptr = prompt->list;
	while (ptr != NULL)
	{
		if (!ptr->argv)
			ptr->argv = space_to_neg_tab(prompt, ptr);
		if (ptr->argv)
			exec_command(prompt, &ptr);
		if (ptr)
			ptr = ptr->next;
	}
}
