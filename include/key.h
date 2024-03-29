/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 22:44:15 by beaujardmae       #+#    #+#             */
/*   Updated: 2021/06/04 15:43:50 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_H
# define KEY_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/inc/libft.h"
# include <limits.h>
# include <sys/errno.h>
# include <string.h>
# include <curses.h>
# include <term.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>

# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif

# define DELETE 127
# define ENTER 13
# define ARROW 27

# define GET 0
# define SET 1
# define FREE 2
# define GET_ERRNO 2
# define SET_ERRNO 3

# define FREE_NOT 0
# define FREE_S1 1
# define FREE_S2 2
# define FREE_ALL 3

#endif