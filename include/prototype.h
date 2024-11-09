/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototype.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:29:07 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/11/09 14:15:13 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPE_H
# define PROTOTYPE_H

# include "struct.h"

void	fatal_error(const char *msg) __attribute__((noreturn));

void	assert_error(const char *msg);

char	*search_path(const char *filename);

// exec

int	exec(t_node *node);

int	open_redir_file(t_node *node);

int	read_heredoc(const char *delimiter);

void	prepare_pipe(t_node *node);

void	prepare_pipe_child(t_node *node);

void	reset_redirect(t_node *redir);

void	prepare_pipe_parent(t_node *node);

void	err_exit(const char *name, const char *err_msg, int estatus);



t_bool	is_blank(char c);

t_bool	startswith(const char *s, const char *keyword);

t_bool	is_operator(const char *s);

t_token	*operators(char **rest, char *line);


void	assert_error(const char *msg);

void	tokenize_error(const char *location, char **rest, char *line);

t_token	*new_token(char *word, t_token_kind kind);

t_token	*tokenize(char *line);


t_bool	is_word(const char *s);

t_bool	is_metacharacter(char c);

t_token	*word(char **rest, char *line);


t_bool	is_redirect(char *line);

t_token	*redirect(char **rest, char *line);


t_bool	consume_blank(char **rest, char *line);


t_node	*expand(t_node *node);

void	append_char(char **s, char c);

char	*single_quote_removal(char *word);

char	*double_quote_removal(char *word);


// parse

t_node	*redirect_out(t_token **rest, t_token *tok);

t_node	*redirect_in(t_token **rest, t_token *tok);

t_node	*redirect_append(t_token **rest, t_token *tok);

t_node	*redirect_heredoc(t_token **rest, t_token *tok);

void	append_tok(t_token **tokens, t_token *tok);

void	append_node(t_node **node, t_node *elm);

t_token	*tokdup(t_token *tok);

t_bool	at_eof(t_token *tok);

t_bool	equal_op(t_token *tok, char *op);

t_node	*new_node(t_node_kind kind);

t_node	*parse(t_token *tok);

// test

void	output_token(t_token *token);

#endif