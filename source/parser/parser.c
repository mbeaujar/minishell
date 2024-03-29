/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 20:18:04 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/05 13:09:31 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_path(char *path, t_type key, int curr_fd)
{
	int	fd;

	fd = -1;
	if (curr_fd != 1 && curr_fd != -1)
		close(curr_fd);
	if (key == DRIGHT)
		fd = open(path, O_APPEND | O_CREAT | O_RDWR, S_IRWXU);
	if (key == RIGHT)
		fd = open(path, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	return (fd);
}

int	open_path(char *path, t_type key, int curr_fd)
{
	int			fd;
	struct stat	file;
	int			tmp;

	fd = -1;
	tmp = -1;
	if (key == RIGHT || key == DRIGHT)
		fd = check_path(path, key, curr_fd);
	else if (key == LEFT)
	{
		if (curr_fd != 0 && curr_fd != -1)
			close(curr_fd);
		if (stat(path, &file) == -1)
			return (-1);
		fd = open(path, O_RDONLY);
	}
	return (fd);
}

int	errno_open(t_cmd *ptr, t_lexer **st, t_type key, int curr_fd)
{
	int		ret;
	char	*path;

	errno = 0;
	path = (*st)->next->token;
	ret = open_path(path, key, curr_fd);
	if (ret == -1)
	{
		ptr->code_errno = errno;
		ptr->path_file = path;
	}
	(*st) = (*st)->next;
	return (ret);
}

t_cmd	*create_token_range(t_lexer **st)
{
	char		*args;
	t_cmd		*list;

	args = NULL;
	list = newlstcommand(NULL);
	while ((*st) != NULL && (*st)->key != COMAT && (*st)->key != PIP)
	{
		if ((*st)->key == DEFAULT)
		{
			ft_unleak_strjoin(&args, (*st)->token);
			if ((*st)->next != NULL && (*st)->next->key == DEFAULT)
				ft_unleak_strjoin(&args, " ");
		}
		if ((*st)->key == RIGHT || (*st)->key == DRIGHT)
			list->std_out = errno_open(list, st, (*st)->key, list->std_out);
		if ((*st)->key == LEFT)
			list->std_in = errno_open(list, st, (*st)->key, list->std_in);
		(*st) = (*st)->next;
	}
	list->args = args;
	return (list);
}

t_cmd	*parse(t_lexer *tokens)
{
	t_lexer		*ptr;
	t_cmd		*list;
	t_cmd		*current;
	char		*args;

	ptr = tokens;
	list = NULL;
	current = NULL;
	args = NULL;
	while (ptr != NULL)
	{
		current = create_token_range(&ptr);
		if (ptr && ptr->key == PIP)
			current->key = PIP;
		if (ptr && (ptr->key == PIP || ptr->key == COMAT))
			ptr = ptr->next;
		lstaddbackcommand(&list, current);
	}
	return (list);
}
