/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:30:49 by yotsubo           #+#    #+#             */
/*   Updated: 2024/11/19 00:14:10 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 本番はグローバル変数として持てないからどうしよう...
int	last_status = 0;

static t_bool	is_numeric(char *s)
{
	long long	num;

	if (!isdigit(*s))
		return (FALSE);
	num = 0;
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (FALSE);
		if (num > LLONG_MAX / 10 || (num == LLONG_MAX / 10 && *s - '0' > LLONG_MAX % 10))
			return (FALSE);
		num *= 10;
		num += *s - '0';
		s++;
	}
	return (TRUE);
}

static void	exit_with_msg(int status)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(status);
}

int	builtin_exit(char **argv)
{
	int	res;

	if (argv[1] == NULL)
		exit_with_msg(last_status);
	if (!is_numeric(argv[1]))
	{
		ft_dprintf(STDERR_FILENO, "exit: %s: numeric argument required\n", argv[1]);
		exit(2);
	}
	if (argv[2])
	{
		ft_dprintf(STDERR_FILENO, "exit: too many arguments\n");
		return (1);
	}
	res = ft_atoi(argv[1]);
	exit_with_msg(res);
	return (0);
}
