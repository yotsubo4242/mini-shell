/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 00:18:48 by yotsubo           #+#    #+#             */
/*   Updated: 2024/10/16 00:18:48 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_bool	g_syntax_error;

void	parse_error(const char *location, t_token **rest, t_token *tok)
{
	g_syntax_error = TRUE;
	dprintf(STDERR_FILENO, "minishell: syntax error near %s\n", location);
	while (tok->kind != TK_EOF)
		tok = tok->next;
	*rest = tok;
}

t_bool	at_eof(t_token *tok)
{
	return (tok->kind == TK_EOF);
}

t_node	*new_node(t_node_kind kind)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	if (!node)
		fatal_error("calloc");
	node->kind = kind;
	return (node);
}

t_token	*tokdup(t_token *tok)
{
	char	*word;

	word = ft_strdup(tok->word);
	if (!word)
		fatal_error("strdup");
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

t_bool	equal_op(t_token *tok, char *op)
{
	if (tok->kind != TK_OP)
		return (FALSE);
	if (!ft_strncmp(tok->word, op, ft_strlen(op)))
		return (TRUE);
	else
		return (FALSE);
}

t_node	*parse(t_token *tok)
{
	t_node	*node;

	return (pipeline(&tok, tok));
}