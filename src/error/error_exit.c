/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkitahar <tkitahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:59:55 by tkitahar          #+#    #+#             */
/*   Updated: 2024/12/03 15:59:55 by tkitahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fatal_error(const char *msg)
{
	perror_prefix();
	ft_dprintf(STDIN_FILENO, "Fatal Error: %s\n", msg);
	perror(NULL);
	exit(1);
}

void	assert_error(const char *msg)
{
	perror_prefix();
	ft_dprintf(STDIN_FILENO, "Assert Error: %s\n", msg);
	exit(255);
}

void	err_exit(const char *location, const char *msg, int status)
{
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "%s: %s:\n", location, msg);
	exit(status);
}
