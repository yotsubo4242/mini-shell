/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:02:34 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/12/13 17:20:54 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_single_quote(char **dst, char **rest, char *p)
{
	if (*p == SINGLE_QUOTE_CHAR)
	{
		p++;
		while (*p != SINGLE_QUOTE_CHAR)
		{
			if (*p == '\0')
				assert_error("Unclosed single quote");
			append_char(dst, *p++);
		}
		p++;
		*rest = p;
	}
	else
		assert_error("Expected single quote");
}

void	remove_double_quote(char **dst, char **rest, char *p)
{
	if (*p == DOUBLE_QUOTE_CHAR)
	{
		p++;
		while (*p != DOUBLE_QUOTE_CHAR)
		{
			if (*p == '\0')
				assert_error("Unclosed double quote");
			append_char(dst, *p++);
		}
		p++;
		*rest = p;
	}
	else
		assert_error("Expected double quote");
}

void	ignore_double_quote_removal(char **dst, char **rest, char *p)
{
	bool	over_firlst_quote;

	over_firlst_quote = false;
	while (*p != '\0')
	{
		if (*p == DOUBLE_QUOTE_CHAR)
		{
			p++;
			if (over_firlst_quote)
				break ;
			over_firlst_quote = true;
		}
		else
		{
			append_char(dst, *p);
			p++;
		}
	}
	*rest = p;
}

static void	deal_with_double_quote(char **new_word, char **rest, \
									char *p, char prev_c)
{
	if (prev_c == '=')
		ignore_double_quote_removal(new_word, rest, p);
	else
		remove_double_quote(new_word, rest, p);
}

void	remove_quote(t_token *tok)
{
	char	*new_word;
	char	*p;
	char	prev_c;

	if (tok == NULL || tok->kind != TK_WORD || \
			tok->word == NULL || tok->is_expanded)
		return ;
	p = tok->word;
	prev_c = '\0';
	new_word = xcalloc(1, sizeof(char));
	while (*p && !is_metacharacter(*p))
	{
		if (*p == SINGLE_QUOTE_CHAR)
			remove_single_quote(&new_word, &p, p);
		else if (*p == DOUBLE_QUOTE_CHAR)
			deal_with_double_quote(&new_word, &p, p, prev_c);
		else
			append_char(&new_word, *p++);
		prev_c = *(p - 1);
	}
	free(tok->word);
	tok->word = new_word;
	remove_quote(tok->next);
}
