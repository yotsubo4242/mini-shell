/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:13:38 by yotsubo           #+#    #+#             */
/*   Updated: 2024/10/30 20:13:38 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_control_operator(t_token *tok)
{
	static char	*const operators[] = {"||", "&", "&&", ";", ";;", "(", ")", "|", "\n"};
	size_t				i;

	i = 0;
	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (startswith(tok->word, operators[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	append_command_element(t_node *cmd, t_token **rest, t_token *tok)
{
	if (tok->kind == TK_WORD)
	{
		append_tok(&(cmd->args), tokdup(tok));
		tok = tok->next;
	} else if (equal_op(tok, "<<") && tok->next->kind == TK_WORD)
		append_node(&(cmd->redirects), redirect_heredoc(&tok, tok));
	else if (equal_op(tok, "<") && tok->next->kind == TK_WORD)
		append_node(&(cmd->redirects), redirect_append(&tok, tok));
	else if (equal_op(tok, ">>") && tok->next->kind == TK_WORD)
		append_node(&(cmd->redirects), redirect_out(&tok, tok));
	else if (equal_op(tok, ">") && tok->next->kind == TK_WORD)
		append_node(&(cmd->redirects), redirect_in(&tok, tok));
	else
		exit(EXIT_FAILURE);
	// TODO: ↑ This should be parse_error()
	*rest = tok;
}

t_node	*simple_command(t_token **rest, t_token *tok)
{
	t_node	*node;

	node = new_node(ND_SIMPLE_CMD);
	append_command_element(node, &tok, tok);
	while (tok && !at_eof(tok) && !is_control_operator(tok))
		append_command_element(node, &tok, tok);
	*rest = tok;
	return (node);
}
