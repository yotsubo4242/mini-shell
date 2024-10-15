/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote_removal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 23:03:40 by yotsubo           #+#    #+#             */
/*   Updated: 2024/10/15 23:03:40 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*double_quote_removal(char *word)
{
	char	*new_word;
	char	*p;

	p = word;
	new_word = NULL;
	while (*p && !is_metacharacter(*p))
	{
		if (*p == DOUBLE_QUOTE_CHAR)
		{
			p++;
			while (*p != DOUBLE_QUOTE_CHAR)
			{
				if (*p == '\0')
					assert_error("Unclosed double quote");
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
