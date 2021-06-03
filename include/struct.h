/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 22:43:04 by beaujardmae       #+#    #+#             */
/*   Updated: 2021/06/01 20:40:25 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "key.h"

typedef enum e_type {
	LEFT,
	RIGHT,
	PIP,
	COMAT,
	PATH,
	DRIGHT,
	DEFAULT = -1,
}			t_type;

typedef struct s_env
{
	char			*name;
	char			*value;
	int				index;
	struct s_env	*next;
}			t_env;

typedef struct s_buffer
{
	char			*buff;
	int				len;
	int				strlen;
	int				modified;
	struct s_buffer	*previous;
	struct s_buffer	*next;
}				t_buff;

typedef struct s_setup
{
	int	debug;
}				t_setup;

typedef struct s_cmd
{
	char			*args;
	char			*path;
	int				std_out;
	char			**argv;
	int				std_in;
	int				code_errno;
	char			*path_file;
	t_type			key;
	struct s_cmd	*previous;
	struct s_cmd	*next;
}		t_cmd;

/*
** returned == $? -- code de retour de la commande
*/

typedef struct s_lexer
{
	char			*token;
	t_type			key;
	struct s_lexer	*previous;
	struct s_lexer	*next;
}		t_lexer;

typedef struct s_lexing
{
	int		i;
	char	*str;
	int		y;
	int		len;
	char	*buffer;
	char	sep;
	int		var;
}		t_lexing;

typedef struct s_prompt
{
	struct termios	raw;
	struct termios	orig_termios;
	t_buff			*buffer;
	int				indice;
	int				isatty;
	t_setup			setup;
	t_lexer			*lexer;
	t_cmd			*list;
	t_env			*env;
	int *pid;
	int *std;
	char *cmd;
	char **args;
	int len_pipe;
	char			**envp;
	int				returned;
}			t_prompt;

#endif