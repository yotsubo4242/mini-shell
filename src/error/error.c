/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkitahar <tkitahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:59:52 by tkitahar          #+#    #+#             */
/*   Updated: 2024/12/03 22:28:22 by tkitahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ERROR_PREFIX "minishell: "

void	perror_prefix(void)
{
	ft_dprintf(STDERR_FILENO, "%s", ERROR_PREFIX);
}

void	xperror2(const char *s1, const char *err_msg)
{
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "%s: ", s1);
	if (err_msg)
		ft_dprintf(STDERR_FILENO, "%s\n", err_msg);
	else 
		perror(NULL);
}

void	xperror3(const char *s1, const char *s2, const char *err_msg)
{
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "%s: ", s1);
	ft_dprintf(STDERR_FILENO, "%s: ", s2);
	if (err_msg)
		ft_dprintf(STDERR_FILENO, "%s\n", err_msg);
	else
		perror(NULL);
}

void	t_err_exit(const char *name, const char *err_msg, int estatus)
{
	ft_dprintf(STDERR_FILENO, "bash: %s: %s\n", name, err_msg);
	exit(estatus);
}
