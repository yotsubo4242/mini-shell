/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:17:12 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/10/21 19:18:49 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	output_token(t_token *token)
{
	while (token->kind != TK_EOF)
	{
		dprintf(STDERR_FILENO, "%s\n", token->word);
		token = token->next;
	}
}