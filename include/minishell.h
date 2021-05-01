/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 20:05:41 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/04/30 20:07:38 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "struct.h"

void ft_putstr(char *str);

//void display_prompt(void);


t_env *fill_env(char **envp);
void delete_env(t_var *var, t_env *to_delete);

t_env *createlstenv(char *env);
void addlstenv(t_env **head, char *env);
void printlstenv(t_env *head);
void freelstenv(t_env *head);
t_env *search_env(t_env *head, char *env_name);

char *return_env_name(char *env);
char *return_env_value(char *env);
t_env *search_env(t_env *head, char *env_name);

void change_directory(t_var *var, char *path);
void cd(t_var *var, char *cmd);

char *get_absolu_path(char *str, size_t size);



char *refresh_value_pwd(char *cwd);
void create_pwd(t_var *var, char *cwd, char *name);
void refresh_pwd(t_var *var);
void change_directory(t_var *var, char *path);
void cd(t_var *var, char *cmd);
void pwd(t_env *head);

void printerrno(void);
char *search_and_replace(char *s, char *search, char *replace, int leak);
int search_where(char *s, char *search);
void prompt(t_var *var, char **envp);
int test_fork(void);
int is_inside(char *s, char im_here);

void unset(t_var *var, char *path);
int is_value(char *env);
t_env	*newexport(char *env);


// ----------------------------------- //

void enablerawmode(struct termios raw);
void disablerawmode(struct termios orig_termios);
void read_stdin(t_prompt *prompt);
void create_termcap(char *termcap);

t_buffer *newlstbuffer(char *buff);
void lstaddfrontbuffer(t_buffer **head, t_buffer *new);
void freelstbuffer(t_buffer **begin);
void printlstbuffer(t_buffer *head);

void expand_buffer(t_prompt *prompt, char c);
void decrease_buffer(t_prompt *prompt);
void display_prompt(t_prompt *prompt);
void isctrl(t_prompt *prompt, char c);

char *new_size_buffer(t_prompt *prompt, char c, char *str, int len);
void lstaddnewbuffer(t_buffer **head, t_buffer *new);
t_buffer *g_buffer(int state, t_buffer *buff);
void reset_buffer(t_prompt *prompt);
char arrow_key(char c, t_prompt *prompt);
void display_prompt(t_prompt *prompt);
void display_buffer(t_prompt *prompt);
void delete_char_prompt(t_prompt *prompt);
void execute_commande(t_prompt *prompt);
char read_key(t_prompt *prompt);
void printbuffer(char *str);

#endif 