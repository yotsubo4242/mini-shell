/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:30:49 by yotsubo           #+#    #+#             */
/*   Updated: 2024/12/05 16:53:41 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_and_exit(int status)
{
	ft_printf("exit\n");
	exit(status);
}

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

	if (argv == NULL)
		print_and_exit(g_last_status);
	if (argv[1] == NULL)
		print_and_exit(g_last_status);
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
		print_and_exit(res);
	}
	xperror2("exit", "numeric argument required");
	return (2);
}
