/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototype.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:29:07 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/10/15 23:05:11 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPE_H
# define PROTOTYPE_H

# include "struct.h"

void	fatal_error(const char *msg) __attribute__((noreturn));

void	assert_error(const char *msg);

char	*search_path(const char *filename);

int		interpret(t_token *tok);


t_bool	is_operator(const char *s);

t_token	*operators(char **rest, char *line);


void	assert_error(const char *msg);

t_token	*new_token(char *word, t_token_kind kind);

t_token	*tokenize(char *line);


t_bool	is_word(const char *s);

t_bool	is_metacharacter(char c);

t_token	*word(char **rest, char *line);


t_bool	consume_blank(char **rest, char *line);


t_token	*expand(t_token *tok);

void	append_char(char **s, char c);

char	*single_quote_removal(char *word);

char	*double_quote_removal(char *word);

#endif