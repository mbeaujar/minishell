/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 20:05:41 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/05/14 20:49:40 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

#include "struct.h"

/*
** SOURCE
*/

void cmd(t_prompt *prompt, char *cmd);
void printerrno_fd(int fd);

/*
** BUILTIN 
*/

void cd(t_prompt *prompt, char **args);
void unset(t_prompt *var, char **unset);
void pwd(t_prompt *prompt);
void env(t_prompt *prompt, char **args);
char *check_args(char **args, int (*fct)());
void export(t_prompt *prompt, char **args);
void exitt(t_prompt *prompt, char **args);
void echoo(t_prompt *prompt, char **args);

/*
** ENV
*/

t_env *fill_env(char **envp, t_prompt *prompt);
void delete_env(t_prompt *var, t_env *to_delete);
t_env *newlstenv(char *env);
int addlstenv(t_env **head, char *env);
void printlstenv(t_env *head);
void freelstenv(t_env *head);
t_env *search_env(t_env *head, char *env_name);
char *return_env_name(char *env);
char *return_env_value(char *env);
int is_value(char *env);
t_env *newlstenvnull(char *env);
int sizelstenv(t_env *head);

void free_tab(char **envp);
char **new_table_env(t_env *head);


/*
** LEXER
*/

t_lexer *newlstlexer(char *token, type key);
void lstaddbacklexer(t_lexer **head, t_lexer *new);
void freelstlexer(t_lexer **begin);
void printlstlexer(t_lexer *head);
int lstsizelexer(t_lexer *head);
void escape_space(char *str, int *i, int state);
void new_token(t_lexer **head, char *buffer, int len, int *y);
void token_backslash(char *str, int *i, char sep);
int token_sep(char *str, int *i, char *sep);
void printlexer(char *str);
t_lexer *lexer(char *str);
int token_type(t_lexing *var, t_lexer **head);
int lexer_error(char sep);


/*
** PARSER
*/

void parse(t_lexer *tokens);
void lstaddbackcommand(t_command **list, t_command *new);
t_command *newlstcommand(char **args);
void printlstcommand(t_command *list);

/*
** PROMPT 
*/

void setup(t_prompt *prompt, int argc, char **argv);

int init_termcaps(void);
int display_termcap(int c);
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
void debug_prompt(t_buffer *buffer, int indice);
void new_line(t_prompt *prompt);


/*
** UTILS 
*/

char *ft_realloc(char *str);
char *ft_create_env(char *s1, char *s2, int state);
char		*ft_strjoin_env(char const *s1, char const *s2);
int ft_strlen_tab(char **str);
void ft_printtab(char **args);
int	ft_strcmp(char *s1, char *s2);
t_env *search_min(t_env *head);

int is_indexable(t_env *head);
int max_index(t_env *head);
void clear_index(t_env *head);
void	ft_unleak_strjoin(char **dst, char *src);
void	ft_argv_strjoin(char **dst, int count, ...);

#endif 