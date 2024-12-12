/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototype.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:29:07 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/12/13 12:33:59 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPE_H
# define PROTOTYPE_H
# include "minishell.h"

void	fatal_error(const char *msg) __attribute__((noreturn));
void	assert_error(const char *msg);
bool	is_directory(const char *path);
char	*search_path(const char *filename);
void	t_err_exit(const char *name, const char *err_msg, int estatus);

// error
void	perror_prefix(void);
void	xperror2(const char *s1, const char *err_msg);
void	xperror3(const char *s1, const char *s2, const char *err_msg);
void	t_err_exit(const char *name, const char *err_msg, int estatus);
void	parse_error(const char *location, t_token **rest, t_token *tok);

// destruct
void	free_argv(char **argv);
void	free_item(t_item *item);
void	free_map(t_map *map);
void	free_char_arys(char **char_arys);
void	free_tok(t_token *tok);
void	free_node(t_node *node);

//builtin
void	builtin_error(const char *cmd_name, const char *msg);
int		builtin_export(char **argv);
int		builtin_exit(char **argv);
int		builtin_env(char **argv);
char	*resolve_pwd(char *oldpwd, char *path);
int		builtin_cd(char **argv);
int		builtin_unset(char **argv);
int		builtin_echo(char **argv);
int		builtin_pwd(char **argv);
int		exec_builtin(t_node *node);
bool	is_builtin(t_node *node);
bool	is_plusminus(char s);
long	ft_strtol(const char *str);

// env
void	cleanup_map(t_map *map);
t_item	*item_new(const char *key, const char *value);
t_map	*map_new(void);
char	*map_get(t_map *map, const char *key);
int		map_put(t_map *map, const char *str);
int		map_set(t_map *map, const char *key, \
				const char *value, bool should_free);
int		map_unset(t_map *map, const char *key);
char	**get_environ(t_map *envmap);
t_map	*init_env(void);

// exec
int		exec(t_node *node);
int		open_redir_file(t_node *node);
int		read_heredoc(const char *delimiter, bool is_delim_unquoted);
void	prepare_pipe(t_node *node);
void	prepare_pipe_child(t_node *node);
bool	is_redirect(t_node *node);
void	do_redirect(t_node *redir);
void	reset_redirect(t_node *redir);
void	prepare_pipe_parent(t_node *node);
void	err_exit(const char *name, const char *err_msg, int estatus);
char	**token_list_to_argv(t_token *tok);

// parse
t_node	*pipeline(t_token **rest, t_token *tok);
t_node	*simple_command(t_token **rest, t_token *tok);
bool	is_blank(char c);
bool	startswith(const char *s, const char *keyword);
bool	is_operator(const char *s);
t_token	*operators(char **rest, char *line);
void	assert_error(const char *msg);
void	tokenize_error(const char *location, char **rest, char *line);
t_token	*new_token(char *word, t_token_kind kind);
t_token	*tokenize(char *line);
bool	is_word(const char *s);
bool	is_metacharacter(char c);
t_token	*word(char **rest, char *line);
t_token	*redirect(char **rest, char *line);
bool	consume_blank(char **rest, char *line);

// expand
void	append_char(char **s, char c);
void	expand(t_node *node);
void	expand_variable_tok(t_token *tok);
void	expand_variable(t_node *node);
void	expand_special_parameter_str(char **dst, char **rest, char *p);
void	expand_variable_str(char **dst, char **rest, char *p);
char	*expand_heardoc_line(char *line);
bool	is_special_parameter(char *s);
bool	is_alpha_num_under(char c);
bool	is_alpha_under(char c);
bool	is_variable(char *s);
void	remove_quote(t_token *tok);
void	remove_single_quote(char **dst, char **rest, char *p);
void	remove_double_quote(char **dst, char **rest, char *p);

// parse
t_node	*redirect_out(t_token **rest, t_token *tok);
t_node	*redirect_in(t_token **rest, t_token *tok);
t_node	*redirect_append(t_token **rest, t_token *tok);
t_node	*redirect_heredoc(t_token **rest, t_token *tok);
void	append_tok(t_token **tokens, t_token *tok);
void	append_node(t_node **node, t_node *elm);
t_token	*tokdup(t_token *tok);
bool	at_eof(t_token *tok);
bool	equal_op(t_token *tok, char *op);
t_node	*new_node(t_node_kind kind);
t_node	*parse(t_token *tok);

// signal
void	setup_signal(void);
void	reset_signal(void);

// test
void	output_token(t_token *token);

// xlib
void	*xcalloc(size_t count, size_t size);
int		xclose(int fd);
int		xdup(int fd);
int		xdup2(int fildes, int fildes2);
void	*xmalloc(size_t size);
int		xpipe(int fildes[2]);
char	*xstrdup(const char *str);

// setget
t_map	*gs_env(int type, t_map *(*set_map)(void));
int		gs_last_status(int type, int last_status);
bool	gs_readline_interrupted(int type, bool readline_interrupted);
bool	gs_syntax_error(int type, bool syntax_error);
char	*gs_line(int type, char *new_line);

#endif
