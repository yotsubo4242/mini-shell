/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:07:58 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/10/14 14:33:05 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_metacharacter(char c)
{
	return (c && ft_strchr("|&;()<> \t\n", c));
}

t_bool	is_word(const char *s)
{
	return (*s && !is_metacharacter(*s));
}

t_token	*word(char **rest, char *line)
{
	const char	*start;
	char		*word;

	start = line;
	while (*line && !is_metacharacter(*line))
		line++;
	word = strndup(start, line - start);
	if (!word)
		fatal_error("strndup");
	*rest = line;
	return (new_token(word, TK_WORD));
}
