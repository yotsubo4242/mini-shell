/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:00:20 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/12/06 18:13:42 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: グローバル変数は後でまとめて大きな構造体に入れる. 
extern bool	g_syntax_error;


t_token	*new_token(char *word, t_token_kind kind)
{
	t_token	*tok;

	tok = xcalloc(1, sizeof(*tok));
	tok->word = word;
	tok->kind = kind;
	tok->is_expanded = false;
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
