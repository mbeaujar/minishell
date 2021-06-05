/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 15:32:57 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/04 17:34:50 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line.h"
#include <stdio.h>

/*
** la fonction return la ligne du fichier txt
*/

char	*ret_line(char *save)
{
	int		i;
	char	*n_line;

	i = 0;
	if (!save)
		return (0);
	while (save[i] && save[i] != '\n')
		i++;
	n_line = malloc(sizeof(char) * (i + 1));
	if (!n_line)
		return (0);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		n_line[i] = save[i];
		i++;
	}
	n_line[i] = '\0';
	return (n_line);
}

/*
** saute la phrase qu'on return dans line +
** garde en memoire les restes du buffer
*/

char	*next_line_buff(char *save)
{
	char	*n_save;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!save)
		return (0);
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (0);
	}
	n_save = malloc(sizeof(char) * ((ft_strlen_gnl(save) - i) + 1));
	if (!n_save)
		return (0);
	i++;
	while (save[i])
		n_save[j++] = save[i++];
	n_save[j] = '\0';
	free(save);
	return (n_save);
}

int	which_return(int ret)
{
	if (ret == 0)
		return (0);
	return (1);
}

char	*free_gnl(char *save)
{
	free(save);
	return (NULL);
}

int	get_next_line(int fd, char **line)
{
	char		*buff;
	static char	*save;
	int			ret;

	ret = 1;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (-1);
	while (!is_endl(save) && ret != 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret == -1)
		{
			free(buff);
			return (-1);
		}
		buff[ret] = '\0';
		save = ft_strjoin_gnl(save, buff);
	}
	free(buff);
	*line = ret_line(save);
	save = free_gnl(save);
	return (which_return(ret));
}
