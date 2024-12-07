/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xdup.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkitahar <tkitahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 21:27:57 by tkitahar          #+#    #+#             */
/*   Updated: 2024/12/07 21:30:35 by tkitahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	xdup(int fd)
{
	int	stashed_fd;

	stashed_fd = dup(fd);
	if (stashed_fd < 0)
		fatal_error("xdup");
	return (stashed_fd);
}
