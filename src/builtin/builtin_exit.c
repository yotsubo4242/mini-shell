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
	arg = argv[1];
	if (is_numeric(arg))
	{
		// TODO is_minus
		// exit (255);
		res = ft_atoi(argv[1]);
		exit(res);
	}
	xperror2("exit", "numeric argument required");
	return (2);
}
