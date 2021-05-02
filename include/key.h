/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 22:44:15 by beaujardmae       #+#    #+#             */
/*   Updated: 2021/05/02 15:43:34 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_H
# define KEY_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> 
#include "../libft/inc/libft.h"
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <curses.h>
#include <term.h>

# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif 

# define DELETE 127
# define ENTER 13
# define ARROW 27
# define GET 0
# define SET 1
# define FREE 2

/* # define TOP 9165
# define BOT 9166
# define LEFT 9168
# define RIGHT 9167 */

/// TERMCAPS \\\

// le -- move cursor left
// dc -- character delete
// cl -- clear term
// nd -- move cursor right
// ce -- delete to end line



#endif 