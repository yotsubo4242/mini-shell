/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkitahar <tkitahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:04:15 by tkitahar          #+#    #+#             */
/*   Updated: 2024/11/12 18:00:46 by tkitahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_variable_str(char **dst, char **rest, char *p)
{
	char	*name;
	char	*value;

	name = ft_calloc(1, sizeof(char));
	if (name == NULL)
		fatal_error("calloc");
	if (*p != '$')
		assert_error("Expected dollar sign");
	p++;
	if (!is_alpha_under(*p))
		assert_error("Variable must starts with alphabet \
				charcter or underscore.");
	append_char(&name, *p++);
	while (is_alpha_num_under(*p))
		append_char(&name, *p++);
	value = getenv(name);
	free(name);
	if (value)
		while (*value)
			append_char(dst, *value++);
	*rest = p;
}

void	append_single_quote(char **dst, char **rest, char *p)
{
	if (*p == SINGLE_QUOTE_CHAR)
	{
		append_char(dst, *p++);
		while (*p != SINGLE_QUOTE_CHAR)
		{
			if (*p == '\0')
				assert_error("Unclosed single quote");
			append_char(dst, *p++);
		}
		append_char(dst, *p++);
		*rest = p;
	}
	else
		assert_error("Expected single quote");
}

void	append_double_quote(char **dst, char **rest, char *p)
{
	if (*p == DOUBLE_QUOTE_CHAR)
	{
		append_char(dst, *p++);
		while (*p != DOUBLE_QUOTE_CHAR)
		{
			if (*p == '\0')
				assert_error("Unclosed double quote");
			else if (is_variable(p))
				expand_variable_str(dst, &p, p);
			else if (is_special_parameter(p))
				expand_special_parameter_str(dst, &p, p);
			else
				append_char(dst, *p++);
		}
		append_char(dst, *p++);
		*rest = p;
	}
	else
		assert_error("Expaected double quote");
}

void	expand_variable_tok(t_token *tok)
{
	char	*new_word;
	char	*p;

	if (tok == NULL || tok->kind != TK_WORD || tok->word == NULL)
		return ;
	p = tok->word;
	new_word = ft_calloc(1, sizeof(char));
	if (new_word == NULL)
		fatal_error("calloc");
	while (*p && !is_metacharacter(*p))
	{
		if (*p == SINGLE_QUOTE_CHAR)
			append_single_quote(&new_word, &p, p);
		else if (*p == DOUBLE_QUOTE_CHAR)
			append_double_quote(&new_word, &p, p);
		else if (is_variable(p))
			expand_variable_str(&new_word, &p, p);
		else if (is_special_parameter(p))
			expand_special_parameter_str(&new_word, &p, p);
		else
			append_char(&new_word, *p++);
	}
	free(tok->word);
	tok->word = new_word;
	expand_variable_tok(tok->next);
}
