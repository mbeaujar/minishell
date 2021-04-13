/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 15:33:20 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/04/10 20:12:05 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define MAX_FD 5

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100

# endif

char		*ret_line(char *save);
char		*next_line_buff(char *save);
int			get_next_line(int fd, char **line);
size_t		ft_strlen(const char *s);
int			is_endl(char *save);
char		*ft_strjoin(char *s1, char *s2);
void		*ft_memmove(void *dst, const void *src, size_t len);

#endif
