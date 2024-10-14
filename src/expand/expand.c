/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:03:03 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/10/14 17:18:41 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*expand(t_token *tok)
{
	t_token	*head;

	head = tok;
	while (head)
	{
		if (head->kind == TK_WORD && head->word && *(head->word) == SINGLE_QUOTE_CHAR)
		{
			head->word = single_quote_removal(head->word);
			// TODO: このエラー処理
			if (!(head->word))
				assert_error("single quote removal");
		}
		head = head->next;
	}
	return (tok);
}