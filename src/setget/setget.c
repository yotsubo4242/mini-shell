/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setget.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkitahar <tkitahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:21:34 by tkitahar          #+#    #+#             */
/*   Updated: 2024/12/11 12:35:19 by tkitahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sg_last_status(int type, int last_status)
{
	static int	status;

	if (type == SET)
		status = last_status;
	return (status);
}

bool	sg_readline_interrupted(int type, bool readline_interrupted)
{
	static	bool	interrupted;

	if (type == SET)
		interrupted = readline_interrupted;
	return (interrupted);
}

bool	sg_syntax_error(int type, bool syntax_error)
{
	static bool	error;

	if (type == SET)
		error = syntax_error;
	return (error);
}

t_map	*sg_env(int type, t_map *(*set_map)(void))
{
	static t_map	*envilon;

	if (type == SET)
		envilon = set_map();
	return (envilon);
}
