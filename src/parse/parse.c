/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 00:18:48 by yotsubo           #+#    #+#             */
/*   Updated: 2024/12/10 18:13:53 by tkitahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern bool	g_syntax_error;

bool	at_eof(t_token *tok)
{
	return (tok->kind == TK_EOF);
}

t_node	*parse(t_token *tok)
{
	return (pipeline(&tok, tok));
}
