/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 22:43:04 by beaujardmae       #+#    #+#             */
/*   Updated: 2021/04/30 14:20:04 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#include "key.h"

typedef struct	s_env
{
	char			*name;
	char			*value;
	int				export;
	int				env;
	struct s_env	*next;
} t_env;

typedef struct s_var
{
	t_env *head;
}		t_var;

typedef struct s_buffer
{
	char *buff;
	int len;
	int strlen;
	int modified;
	struct s_buffer *previous;
	struct s_buffer *next;
}				t_buffer;

typedef struct s_prompt
{
	struct termios raw;
	struct termios orig_termios;
	t_buffer *buffer;
	int  indice;
	int limit_buffer;
	int modified;
} t_prompt;



#endif