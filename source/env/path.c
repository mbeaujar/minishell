/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 17:50:00 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/02 22:30:20 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*recup_real_path(void)
{
	int		fd;
	int		ret;
	char	*path;
	char	*new;

	fd = open("/etc/environment", O_RDONLY);
	if (fd == -1)
		return (ft_create_env("PATH", NULL, FREE_NOT));
	ret = get_next_line(fd, &path);
	if (ret == -1)
	{
		close(fd);
		return (ft_create_env("PATH", NULL, FREE_NOT));
	}
	close(fd);
	new = ft_strtrim(path, "\"");
	free(path);
	return (ft_create_env("PATH", new, FREE_S2));
}

void	find_env_path(t_prompt *prompt)
{
	t_env	*find;

	find = search_env(prompt->env, "_");
	if (find)
		find->index = -2;
	find = search_env(prompt->env, "PATH");
	if (!find)
		addlstenv(&prompt->env, recup_real_path());
	else if (!find->value)
		find->value = recup_real_path();
}
