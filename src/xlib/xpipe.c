/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpipe.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkitahar <tkitahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:02:40 by tkitahar          #+#    #+#             */
/*   Updated: 2024/12/03 14:07:39 by tkitahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	xpipe(int fildes[2])
{
	int	ret;

	ret = pipe(fildes);
	if (ret < 0)
		fatal_error("xpipe");
	return (ret);
}
