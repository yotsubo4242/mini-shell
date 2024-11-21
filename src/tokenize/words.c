/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:07:58 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/10/15 23:51:26 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_metacharacter(char c)
{
	return (c && ft_strchr("|&;()<> \t\n", c));
}

bool	is_word(const char *s)
{
	return (*s && !is_metacharacter(*s));
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
			line++;
			while (*line != SINGLE_QUOTE_CHAR)
			{
				// TODO: when unclosed single quote.
				if (*line == '\0')
				{
					tokenize_error("Unclosed single quote", rest, line);
					return (new_token(NULL, TK_EOF));
				}
				line++;
			}
			line++;
		} else if (*line == DOUBLE_QUOTE_CHAR) {
			line++;
			while (*line != DOUBLE_QUOTE_CHAR)
			{
				// TODO: when unclosed double quote.
				if (*line == '\0')
				{
					tokenize_error("Unclosed double quote", rest, line);
					return (new_token(NULL, TK_EOF));
				}
				line++;
			}
			line++;
		}
		else
			line++;
	}
	word = strndup(start, line - start);
	if (!word)
		fatal_error("strndup");
	*rest = line;
	return (new_token(word, TK_WORD));
}
