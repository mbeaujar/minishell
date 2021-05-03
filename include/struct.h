/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atinseau <atinseau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 22:43:04 by beaujardmae       #+#    #+#             */
/*   Updated: 2021/05/03 12:09:17 by atinseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#include "key.h"

typedef struct	s_env
{
	char			*name;
	char			*value;
	int				index;
	struct s_env	*next;
} t_env;

typedef struct s_buffer
{
	char *buff;
	int len;
	int strlen;
	int modified;
	struct s_buffer *previous;
	struct s_buffer *next;
}				t_buffer;

typedef struct s_setup
{
	int debug;
} t_setup;

typedef struct s_prompt
{
	struct termios raw;
	struct termios orig_termios;
	t_buffer *buffer;
	int  indice;
	int limit_buffer;
	int modified;
	t_env *env;
	t_setup setup;
} t_prompt;



#endif