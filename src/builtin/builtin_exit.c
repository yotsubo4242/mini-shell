/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:30:49 by yotsubo           #+#    #+#             */
/*   Updated: 2024/12/10 16:41:06 by tkitahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_plusminus(char s)
{
	return (s == '-' || s == '+');
}

static void	print_and_exit(int status)
{
	ft_dprintf(STDERR_FILENO, "exit\n");
	exit (status);
}

static bool	is_numeric(char *s)
{
	while (ft_isspace(*s))
		s++;
	if (is_plusminus(*s))
		s++;
	if (!*s)
		return (false);
	while (*s)
	{
		if (ft_isspace(*s))
			break ;
		if (!ft_isdigit(*s))
			return (false);
		s++;
	}
	while (ft_isspace(*s))
	{
		if (*s == '\n')
			return (false);
		s++;
	}
	return (true);
}

int	builtin_exit(char **argv)
{
	long	res;
	char	*arg;

	if (argv == NULL || argv[1] == NULL)
		print_and_exit(sg_last_status(GET, NULL));
	if (argv[2])
	{
		xperror2("exit", "too many arguments");
		return (1);
	}
	arg = argv[1];
	if (!is_numeric(arg))
	{
		xperror2("exit", "numeric argument required");
		return (2);
	}
	errno = 0;
	res = ft_strtol(arg);
	if (errno != ERANGE)
		print_and_exit(res);
	xperror2("exit", "numeric argument required");
	return (2);
}
