/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 15:08:24 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/01 19:46:47 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	secure_free(char *str)
{
	if (str)
		free(str);
}

int	is_return_var(char *str, int i)
{
	if (str[i] == '$' && str[i + 1]
		&& str[i + 1] == '?' && !is_endvar(str[i + 2]))
		return (1);
	return (0);
}

char	*add_value_return_var(t_prompt *prompt, char *str, int i)
{
	char	*prev;
	int		len_str;
	char	*ret;
	char	*next;

	next = NULL;
	ret = NULL;
	len_str = (int)ft_strlen(str);
	if (str[i + 2] != 0)
		next = ft_substr(str, i + 2, len_str - i);
	prev = ft_substr(str, 0, i);
	ret = ft_itoa(prompt->returned);
	ft_unleak_strjoin(&prev, ret);
	secure_free(ret);
	ft_unleak_strjoin(&prev, next);
	secure_free(next);
	secure_free(str);
	return (prev);
}

char	*add_tildes_var(t_prompt *prompt, char *str, int i)
{
	t_env	*find;
	char	*prev;
	int		len_str;
	char	*ret;
	char	*next;

	find = search_env(prompt->env, "HOME");
	if (!find)
		return (str);
	next = NULL;
	ret = "";
	len_str = (int)ft_strlen(str);
	if (str[i + 1] != 0)
		next = ft_substr(str, i + 1, len_str - i);
	prev = ft_substr(str, 0, i);
	if (find->value)
		ret = find->value;
	ft_unleak_strjoin(&prev, ret);
	ft_unleak_strjoin(&prev, next);
	secure_free(str);
	secure_free(next);
	return (prev);
}
