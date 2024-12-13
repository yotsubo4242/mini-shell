/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:34:14 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/12/13 17:44:08 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_control_operator_exit(bool res, char **operators)
{
	free_argv(operators);
	return (res);
}

bool	is_control_operator(t_token *tok)
{
	char	**operators;
	size_t	i;

	operators = make_operators();
	i = 0;
	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (startswith(tok->word, operators[i]))
			return (is_control_operator_exit(true, operators));
		i++;
	}
	return (is_control_operator_exit(false, operators));
}

void	append_command_element(t_node *cmd, t_token **rest, t_token *tok)
{
	if (tok->kind == TK_WORD)
	{
		append_tok(&(cmd->args), tokdup(tok));
		tok = tok->next;
	}
	else if (equal_op(tok, "<<") && tok->next->kind == TK_WORD)
		append_node(&(cmd->redirects), redirect_heredoc(&tok, tok));
	else if (equal_op(tok, "<") && tok->next->kind == TK_WORD)
		append_node(&(cmd->redirects), redirect_in(&tok, tok));
	else if (equal_op(tok, ">>") && tok->next->kind == TK_WORD)
		append_node(&(cmd->redirects), redirect_append(&tok, tok));
	else if (equal_op(tok, ">") && tok->next->kind == TK_WORD)
		append_node(&(cmd->redirects), redirect_out(&tok, tok));
	else
		parse_error("append_command_element", &tok, tok);
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

t_node	*pipeline(t_token **rest, t_token *tok)
{
	t_node	*node;

	node = new_node(ND_PIPELINE);
	node->inpipe[0] = STDIN_FILENO;
	node->inpipe[1] = -1;
	node->outpipe[0] = -1;
	node->outpipe[1] = STDOUT_FILENO;
	node->command = simple_command(&tok, tok);
	if (equal_op(tok, "|"))
		node->next = pipeline(&tok, tok->next);
	*rest = tok;
	return (node);
}
