/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_control_operator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:51:25 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/12/13 18:04:28 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_control_operator_exit(bool res, char **operators)
{
	free_argv(operators);
	return (res);
}

static char	**make_control_operators(void)
{
	char	**operators;

	operators = xcalloc(10, sizeof(char *));
	operators[0] = xstrdup("||");
	operators[1] = xstrdup("&");
	operators[2] = xstrdup("&&");
	operators[3] = xstrdup(";");
	operators[4] = xstrdup(";;");
	operators[5] = xstrdup("(");
	operators[6] = xstrdup(")");
	operators[7] = xstrdup("|");
	operators[8] = xstrdup("\n");
	operators[9] = NULL;
	return (operators);
}

bool	is_control_operator(t_token *tok)
{
	char	**operators;
	size_t	i;

	operators = make_control_operators();
	i = 0;
	while (operators[i])
	{
		if (startswith(tok->word, operators[i]))
			return (is_control_operator_exit(true, operators));
		i++;
	}
	return (is_control_operator_exit(false, operators));
}
