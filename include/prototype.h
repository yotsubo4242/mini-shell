/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototype.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:29:07 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/10/14 17:16:41 by yuotsubo         ###   ########.fr       */
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

char	*single_quote_removal(char *word);

#endif