/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 20:05:41 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/04/14 17:02:05 by mbeaujar         ###   ########.fr       */
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
#  define PATH_MAX 4096
# endif 

typedef struct s_env
{
	char *name;
	char *value;
	struct s_env *next;
} t_env;

void ft_putstr(char *str);

void prompt(t_env *head);
void display_prompt(void);


t_env *fill_env(char **envp);
void addlstenv(t_env **head, char *env);
void freelstenv(t_env *head);
void printlstenv(t_env *head);
char *return_env_name(char *env);
char *return_env_value(char *env);
t_env *search_env(t_env *head, char *env_name);

void change_directory(t_env *head, char *path);
void cd(t_env *head, char *cmd);

char *get_absolu_path(char *str, size_t size);


#endif 