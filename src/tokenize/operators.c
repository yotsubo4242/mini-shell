/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:16:03 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/12/13 14:54:13 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	startswith(const char *s, const char *keyword)
{
	return (!ft_memcmp(s, keyword, ft_strlen(keyword)));
}

static bool	is_operator_exit(bool res, char **operators)
{
	free_argv(operators);
	return (res);
}

static char	**make_operators(void)
{
	char	**operators;

	operators = xcalloc(14, sizeof(char *));
	operators[0] = xstrdup("<<");
	operators[1] = xstrdup(">>");
	operators[2] = xstrdup("<");
	operators[3] = xstrdup(">");
	operators[4] = xstrdup("||");
	operators[5] = xstrdup("&");
	operators[6] = xstrdup("&&");
	operators[7] = xstrdup(";");
	operators[8] = xstrdup(";;");
	operators[9] = xstrdup("(");
	operators[10] = xstrdup(")");
	operators[11] = xstrdup("|");
	operators[12] = xstrdup("\n");
	operators[13] = NULL;
	return (operators);
}

bool	is_operator(const char *s)
{
	char	**operators;
	size_t	i;

	operators = make_operators();
	i = 0;
	while (operators[i])
	{
		if (startswith(s, operators[i]))
			return (is_operator_exit(true, operators));
		i++;
	}
	return (is_operator_exit(false, operators));
}

t_token	*operators(char **rest, char *line)
{
	char	**operators;
	size_t	i;
	char	*op;

	operators = make_operators();
	i = 0;
	while (operators[i])
	{
		if (startswith(line, operators[i]))
		{
			op = xstrdup(operators[i]);
			*rest = line + ft_strlen(op);
			free_argv(operators);
			return (new_token(op, TK_OP));
		}
		i++;
	}
	free_argv(operators);
	assert_error("Unexpected operator");
	return (NULL);
}
