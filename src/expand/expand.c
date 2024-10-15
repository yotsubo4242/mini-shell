/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:03:03 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/10/16 00:30:35 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*expand(t_node *node)
{
	t_token	*head;

	head = node->args;
	while (head)
	{
		if (head->kind == TK_WORD && head->word && *(head->word) == SINGLE_QUOTE_CHAR)
		{
			head->word = single_quote_removal(head->word);
			// TODO: このエラー処理
			if (!(head->word))
				assert_error("single quote removal");
		} else if (head->kind == TK_WORD && head->word && *(head->word) == DOUBLE_QUOTE_CHAR) {
			head->word = double_quote_removal(head->word);
			// TODO: このエラー処理
			if (!(head->word))
				assert_error("double quote removal");
		}
		head = head->next;
	}
	return (node);
}