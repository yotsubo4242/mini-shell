/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote_removal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:02:34 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/10/14 17:22:19 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_char(char **s, char c)
{
	size_t	size;
	char	*new;

	size = 2;
	if (*s)
		size += ft_strlen(*s);
	new = (char *)malloc(sizeof(char) * size);
	if (!new)
		fatal_error("malloc");
	if (*s)
		ft_strlcpy(new, *s, size);
	new[size - 2] = c;
	new[size - 1] = '\0';
	if (*s)
		free(*s);
	*s = new;
}

char	*single_quote_removal(char *word)
{
	char	*new_word;
	char	*p;

	p = word;
	new_word = NULL;
	while (*p && !is_metacharacter(*p))
	{
		if (*p == SINGLE_QUOTE_CHAR)
		{
			p++;
			while (*p != SINGLE_QUOTE_CHAR)
			{
				if (*p == '\0')
					assert_error("Unclosed single quote");
				append_char(&new_word, *p);
				p++;
			}
			p++;
		}
		else
			append_char(&new_word, *p++);
	}
	free(word);
	return (new_word);
}
