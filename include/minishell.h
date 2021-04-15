/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 20:05:41 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/04/15 19:41:15 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> 
#include "../libft/inc/libft.h"
#include <limits.h>
#include <errno.h>
#include <string.h>

# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif 

typedef struct s_env
{
	char *name;
	char *value;
	struct s_env *next;
} t_env;

typedef struct s_var
{
	t_env *head;
}		t_var;


void ft_putstr(char *str);

void prompt(t_var *var);
void display_prompt(void);

/*
** env_create.c
*/

t_env *fill_env(char **envp);
void delete_env(t_var *var, t_env *to_delete);

/*
** env_linked_list.c
*/

t_env *newlstenv(char *env);
void addlstenv(t_env **head, char *env);
void printlstenv(t_env *head);
void freelstenv(t_env *head);
t_env *search_env(t_env *head, char *env_name);

/*
** env_parsing.c
*/

char *return_env_name(char *env);
char *return_env_value(char *env);

/*
** builtin_cd.c
*/

void refresh_pwd(t_var *var);
void change_directory(t_var *var, char *path);
void cd(t_var *var, char *cmd);
void pwd(t_env *head);

/*
** main.c 
*/

void printerrno(void);

#endif 