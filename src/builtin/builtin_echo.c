/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:26:20 by tkitahar          #+#    #+#             */
/*   Updated: 2024/12/12 18:12:36 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_n(char *argv)
{
	if (*argv != '-')
		return (false);
	while (*++argv)
	{
		if (*argv != 'n')
		{
			return (false);
		}
	}
	return (true);
}

int	builtin_echo(char **argv)
{
	bool	is_first_arg;
	bool	echo_newline;
	size_t	i;

	i = 1;
	echo_newline = true;
	while (argv[i] && is_n(argv[i]))
	{
		i++;
		echo_newline = false;
	}
	is_first_arg = true;
	while (argv[i])
	{
		if (!is_first_arg)
			write(STDOUT_FILENO, " ", 1);
		is_first_arg = false;
		write(STDOUT_FILENO, argv[i], ft_strlen(argv[i]));
		i++;
	}
	if (echo_newline)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
