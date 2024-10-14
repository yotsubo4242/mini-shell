/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototype.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:29:07 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/10/14 14:57:09 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPE_H
# define PROTOTYPE_H

# include "struct.h"

void	fatal_error(const char *msg) __attribute__((noreturn));

void	assert_error(const char *msg);


t_bool	is_operator(const char *s);

t_token	*operators(char **rest, char *line);


void	assert_error(const char *msg);

t_token	*tokenize(char *line);


t_bool	is_word(const char *s);

t_token	*word(char **rest, char *line);


t_bool	consume_blank(char **rest, char *line);

#endif