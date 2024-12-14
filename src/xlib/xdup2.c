/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xdup2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkitahar <tkitahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:58:27 by tkitahar          #+#    #+#             */
/*   Updated: 2024/12/03 14:00:43 by tkitahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	xdup2(int fildes, int fildes2)
{
	int	fd;

	fd = dup2(fildes, fildes2);
	if (fd < 0)
		fatal_error("xdup2");
	return (fd);
}
