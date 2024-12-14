/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:03:03 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/11/12 17:57:03 by tkitahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_variable(t_node *node)
{
	if (node == NULL)
		return ;
	expand_variable_tok(node->args);
	expand_variable_tok(node->filename);
	expand_variable(node->redirects);
	expand_variable(node->command);
	expand_variable(node->next);
}

void	expand_quote_removal(t_node *node)
{
	if (node == NULL)
		return ;
	remove_quote(node->args);
	remove_quote(node->filename);
	remove_quote(node->delimiter);
	expand_quote_removal(node->redirects);
	expand_quote_removal(node->command);
	expand_quote_removal(node->next);
}

void	expand(t_node *node)
{
	expand_variable(node);
	expand_quote_removal(node);
}
