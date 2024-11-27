/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:00:20 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/11/09 16:52:59 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: グローバル変数は後でまとめて大きな構造体に入れる. 
extern bool	g_syntax_error;

void	assert_error(const char *msg)
{
	ft_dprintf(STDERR_FILENO, "%s\n", msg);
}

void	tokenize_error(const char *location, char **rest, char *line)
{
	g_syntax_error = TRUE;
	ft_dprintf(STDERR_FILENO, "minishell: syntax error near %s\n", location);
	while (*line)
		line++;
	*rest = line;
}

t_token	*new_token(char *word, t_token_kind kind)
{
	t_token	*tok;

	tok = ft_calloc(1, sizeof(*tok));
	if (!tok)
		fatal_error("calloc");
	tok->word = word;
	tok->kind = kind;
	return (tok);
}

t_token	*tokenize(char *line)
{
	t_token	head;
	t_token	*tok;

	head.next = NULL;
	tok = &head;
	while (*line)
	{
		if (consume_blank(&line, line))
			continue ;
		else if (is_operator(line))
		{
			tok->next = operators(&line, line);
			tok = tok->next;
		} else if (is_word(line)) {
			tok->next = word(&line, line);
			tok = tok->next;
		} else
			tokenize_error("Unexpected Token", &line, line);
	}
	tok->next = new_token(NULL, TK_EOF);
	//output_token(&head);
	return (head.next);
}