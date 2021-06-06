/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 20:05:41 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/06 17:02:21 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "struct.h"

/*
** SOURCE
*/

void	cmd(t_prompt *prompt, char *str);
void	printerrno_fd(int fd);

/*
** BUILTIN 
*/

void	cd(t_prompt *prompt, char **args);
int		is_valid_identifier(char *str);
void	unset(t_prompt *var, char **unset);
void	pwd(t_prompt *prompt, char **args);
void	env(t_prompt *prompt, char **args);
char	*check_args(char **args, int (*fct)());
void	export(t_prompt *prompt, char **args);
t_env	*search_index(t_env *head, int index);
void	exitt(t_prompt *prompt, char **args);
void	free_all(t_prompt *prompt, char **args, unsigned char returned);
void	echoo(t_prompt *prompt, char **args);

/*
** ENV
*/

t_env	*fill_env(char **envp);
void	delete_env(t_prompt *var, t_env *to_delete);
t_env	*newlstenv(char *env);
int		addlstenv(t_env **head, char *env);
void	printlstenv(t_env *head);
void	freelstenv(t_env **head);
t_env	*search_env(t_env *head, char *env_name);
char	*return_env_name(char *env);
char	*return_env_value(char *env);
int		is_value(char *env);
t_env	*newlstenvnull(char *env);
int		sizelstenv(t_env *head);
void	find_env_path(t_prompt *prompt);

int		free_tab(char **envp);
char	**new_table_env(t_env *head);
void	find_env_shlvl(t_prompt *prompt);

/*
** LEXER
*/

t_lexer	*newlstlexer(char *token, t_type key);
void	lstaddbacklexer(t_lexer **head, t_lexer *new);
void	freelstlexer(t_lexer **begin);
void	printlstlexer(t_lexer *head);
int		lstsizelexer(t_lexer *head);
void	escape_space(char *str, int *i, int state);
void	new_token(t_lexer **head, char *buffer, int len, int *y);
void	token_backslash(char *str, int *i, char sep);
int		token_sep(char *str, int *i, char *sep, int *var);
void	printlexer(char *str);
int		count_redir(char *str, char redir);
int		count_comat(char *str);
int		count_pip(char *str);
int		is_redir(t_type key);
int		is_double_sep(t_type key1, t_type key2);
t_lexer	*lexer(t_prompt *prompt, char *str);
int		check_token(t_lexer *head);
int		token_type(t_lexing *var, t_lexer **head);
int		lexer_error(char sep);
int		is_sep(char c);

/*
** PARSER
*/

t_cmd	*parse(t_lexer *tokens);
void	lstaddbackcommand(t_cmd **list, t_cmd *new);
char	*replace_occurence(char *src, char *key, char *value);
void	search_variable(t_cmd *ptr, t_prompt *prompt);
int		command_not_found(t_prompt *prompt, char **args);
int		is_endvar(char c);
int		is_return_var(char *str, int i);
char	*add_value_return_var(t_prompt *prompt, char *str, int i);
char	*add_tildes_var(t_prompt *prompt, char *str, int i);
void	secure_free(char *str);
void	redir(t_cmd *ptr);
int		check_errno(int ret);
void	close_redir(t_cmd *ptr);
void	exec_pipe(t_prompt *prompt, t_cmd *ptr, t_cmd *next);
void	which_command(t_prompt *prompt, t_cmd *ptr, char **args);
void	unbuiltin(t_prompt *prompt, t_cmd *ptr, char **args);
t_cmd	*newlstcommand(char *args);
void	printlstcommand(t_cmd *list);
void	interpreter(t_prompt *prompt);
void	freelstcommand(t_cmd **list);
int		is_valid_command(t_prompt *prompt, t_cmd *list, char **args);
char	**space_to_neg_tab(t_prompt *prompt, t_cmd *ptr);

int		nbpipe(t_cmd *ptr);
void	free_fork(t_prompt *prompt);

void	build_pipe(t_prompt *prompt, t_cmd *ptr);

/*
** PROMPT 
*/

void	setup(t_prompt *prompt, int argc, char **argv);
void	exit_debug(t_prompt *prompt);

int		init_termcaps(void);
int		display_termcap(int c);
void	enablerawmode(struct termios raw);
void	disablerawmode(struct termios orig_termios);
void	read_stdin(t_prompt *prompt);
void	create_termcap(char *termcap);

t_buff	*newlstbuffer(char *buff);
void	lstaddfrontbuffer(t_buff **head, t_buff *new);
void	freelstbuffer(t_buff **begin);
void	printlstbuffer(t_buff *head);

void	expand_buffer(t_prompt *prompt, char c);
void	decrease_buffer(t_prompt *prompt);
void	display_prompt(t_prompt *prompt);
void	isctrl(t_prompt *prompt, char c);

char	*new_size_buffer(t_prompt *prompt, char c, char *str, int len);
void	lstaddnewbuffer(t_buff **head, t_buff *new);
t_buff	*g_buffer(int state, t_buff *buff);
void	reset_buff(t_prompt *prompt);
char	arrow_key(char c, t_prompt *prompt);
void	display_prompt(t_prompt *prompt);
void	display_buffer(t_prompt *prompt);
void	delete_char_prompt(t_prompt *prompt);
void	execute_commande(t_prompt *prompt);
char	read_key(t_prompt *prompt);
void	printbuffer(char *str);
void	debug_prompt(t_buff *buffer, int indice);
void	new_line(t_prompt *prompt);
void	prompt_non_tty(t_prompt *prompt);
char    is_ctrl_arrow(t_prompt *prompt, char c, char first, char second);
void move_right(t_prompt *prompt);
void move_left(t_prompt *prompt);

/*
** UTILS 
*/

char	*ft_realloc(char *str);
char	*ft_create_env(char *s1, char *s2, int state);
char	*ft_strjoin_env(char const *s1, char const *s2);
int		ft_strlen_tab(char **str);
void	ft_printtab(char **args);
int		ft_strcmp(char *s1, char *s2);
t_env	*search_min(t_env *head);

int		is_indexable(t_env *head);
int		max_index(t_env *head);
void	clear_index(t_env *head);
void	ft_unleak_strjoin(char **dst, char *src);
void	ft_argv_strjoin(char **dst, int count, ...);
char	*ft_secure_strdup(const char *str);
char	*ft_strfrom_tab(char **argv, char *sep);

#endif 