/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:07:58 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/12/13 15:57:52 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	skip_single_quote(char **rest, char *line)
{
	line++;
	while (*line != SINGLE_QUOTE_CHAR)
	{
		if (*line == '\0')
		{
			*rest = line;
			return (false);
		}
		line++;
	}
	line++;
	*rest = line;
	return (true);
}

static bool	skip_double_quote(char **rest, char *line)
{
	line++;
	while (*line != DOUBLE_QUOTE_CHAR)
	{
		if (*line == '\0')
		{
			*rest = line;
			return (false);
		}
		line++;
	}
	line++;
	*rest = line;
	return (true);
}

static t_token	*word_error(char ***rest, char *line, char type)
{
	if (type == SINGLE_QUOTE_CHAR)
		tokenize_error("Unclosed single quote", *rest, line);
	else if (type == DOUBLE_QUOTE_CHAR)
		tokenize_error("Unclosed double quote", *rest, line);
	return (new_token(NULL, TK_EOF));
}

t_token	*word(char **rest, char *line)
{
	const char	*start;
	char		*word;

	start = line;
	while (*line && !is_metacharacter(*line))
	{
		if (*line == SINGLE_QUOTE_CHAR)
		{
			if (!skip_single_quote(&line, line))
				return (word_error(&rest, line, SINGLE_QUOTE_CHAR));
		}
		else if (*line == DOUBLE_QUOTE_CHAR)
		{
			if (!skip_double_quote(&line, line))
				return (word_error(&rest, line, DOUBLE_QUOTE_CHAR));
		}
		else
			line++;
	}
	word = ft_strldup(start, line - start);
	if (!word)
		fatal_error("strldup");
	*rest = line;
	return (new_token(word, TK_WORD));
}
