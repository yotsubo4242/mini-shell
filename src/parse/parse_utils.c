/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkitahar <tkitahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:13:05 by tkitahar          #+#    #+#             */
/*   Updated: 2024/12/10 18:13:45 by tkitahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
