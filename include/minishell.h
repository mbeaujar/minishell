/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 20:05:41 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/04/13 18:40:32 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> 
#include "../libft/inc/libft.h"

typedef struct s_env
{
	char *name;
	char *value;
	struct s_env *next;
} t_env;

void ft_putstr(char *str);

/*
** prompt
*/ 

void prompt(void);
void display_prompt(void);

/*
** env
*/

t_env *fill_env(char **envp);
void addlstenv(t_env **head, char *env);
void freelstenv(t_env *head);
void printlstenv(t_env *head);
char *return_env_name(char *env);
char *return_env_value(char *env);


#endif 