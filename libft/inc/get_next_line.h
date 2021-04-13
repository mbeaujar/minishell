/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 15:33:20 by mbeaujar          #+#    #+#             */
/*   Updated: 2020/12/11 18:36:39 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# define MAX_FD 1024

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100

# endif

char		*ret_line(char *save);
char		*next_line_buff(char *save);
int			get_next_line(int fd, char **line);
size_t		ft_strlen_gnl(const char *s);
int			is_endl(char *save);
char		*ft_strjoin_gnl(char *s1, char *s2);
void		*ft_memmove_gnl(void *dst, const void *src, size_t len);

#endif
