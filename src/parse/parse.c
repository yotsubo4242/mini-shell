/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 00:18:48 by yotsubo           #+#    #+#             */
/*   Updated: 2024/12/03 14:26:11 by tkitahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern bool	g_syntax_error;

void	parse_error(const char *location, t_token **rest, t_token *tok)
{
	g_syntax_error = TRUE;
	ft_dprintf(STDERR_FILENO, "minishell: syntax error near %s\n", location);
	while (tok->kind != TK_EOF)
		tok = tok->next;
	*rest = tok;
}

bool	at_eof(t_token *tok)
{
	return (tok->kind == TK_EOF);
}

t_node	*new_node(t_node_kind kind)
{
	t_node	*node;

	node = xcalloc(1, sizeof(t_node));
	node->kind = kind;
	return (node);
}

t_token	*tokdup(t_token *tok)
{
	char	*word;

	word = xstrdup(tok->word);
	return (new_token(word, tok->kind));
}

void	append_tok(t_token **tokens, t_token *tok)
{
	if (*tokens == NULL)
	{
		*tokens = tok;
		return ;
	}
	append_tok(&(*tokens)->next, tok);
}

void	append_node(t_node **node, t_node *elm)
{
	if (*node == NULL)
	{
		*node = elm;
		return ;
	}
	append_node(&((*node)->next), elm);
}

bool	equal_op(t_token *tok, char *op)
{
	if (tok->kind != TK_OP)
		return (FALSE);
	if (!ft_strcmp(tok->word, op))
		return (TRUE);
	else
		return (FALSE);
}

t_node	*parse(t_token *tok)
{
	return (pipeline(&tok, tok));
}
