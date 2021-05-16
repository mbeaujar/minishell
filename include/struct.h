/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 22:43:04 by beaujardmae       #+#    #+#             */
/*   Updated: 2021/05/14 20:21:28 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef STRUCT_H
# define STRUCT_H

#include "key.h"

// STDERR_FILENO, STDIN_FILENO, STDOUT_FILENO

typedef enum type {
	LEFT,
	RIGHT,
	PIP,
	COMAT,
	PATH,
	DEFAULT = -1,
} type;

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

typedef struct s_command
{
    char **args;
	
    int std_out;
    int std_in;
    int std_err;

	type key;

    struct s_command *previous;
    struct s_command *next;
} t_command;

/*
** returned == $? -- code de retour de la commande
*/

typedef struct s_lexer
{
	char *token;
	type key; 
	struct s_lexer *previous;
	struct s_lexer *next;
} t_lexer;

typedef struct s_lexing
{
	int i;
	char *str;
	int y;
	int len;
	char *buffer;
	char sep;
} t_lexing;

typedef struct s_prompt
{
	struct termios raw;
	struct termios orig_termios;
	t_buffer *buffer;
	int  indice;
	char **envp;
	t_setup setup;
	t_command *list;
	t_env *env;
	int returned;
} t_prompt;



#endif