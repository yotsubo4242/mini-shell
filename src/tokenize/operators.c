/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:16:03 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/10/14 14:31:04 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	startswith(const char *s, const char *keyword)
{
	retur (!ft_memcmp(s, keyword, ft_strlen(keyword)));
}

t_bool	is_operator(const char *s)
{
	static char *const	operators[] = {"||", "&", "&&", ";", ";;", "(", ")", "|", "\n"};
	size_t				i;

	i = 0;
	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (startswith(s, operators[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_token	*operator(char **rest, char *line)
{
	static char *const	operators[] = {"||", "&", "&&", ";", ";;", "(", ")", "|", "\n"};
	size_t				i;
	char				*op;

	i = 0;
	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (startswith(line, operators[i]))
		{
			op = ft_strdup(operators[i]);
			if (!op)
				fatal_error("strdup");
			*rest = line + ft_strlen(op);
			return (new_token(op, TK_OP));
		}
		i++;
	}
	assert_error("Unexpected operator");
}
