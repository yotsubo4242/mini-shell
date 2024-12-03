/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:30:49 by yotsubo           #+#    #+#             */
/*   Updated: 2024/11/21 14:07:55 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: argv[1]が負数の時の対応
static bool	is_numeric(char *s)
{
	long long	num;

	if (!isdigit(*s))
		return (false);
	num = 0;
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (false);
		if (num > LLONG_MAX / 10 || (num == LLONG_MAX / 10 && *s - '0' > LLONG_MAX % 10))
			return (false);
		num *= 10;
		num += *s - '0';
		s++;
	}
	return (true);
}

int	builtin_exit(char **argv)
{
	long	res;
	char	*arg;

	if (argv[1] == NULL)
		exit(g_last_status);
	if (argv[2])
	{
		xperror2("exit", "too many arguments");
		return (1);
	}
	if (is_numeric(argv[1]))
	{
		xperror3("exit", "numeric argument required", argv[1]);
		exit(2);
	}
	res = ft_atoi(argv[1]);
	exit_with_msg(res);
	return (0);
}
