/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:21:34 by tkitahar          #+#    #+#             */
/*   Updated: 2024/12/13 14:02:50 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	gs_last_status(int type, int last_status)
{
	static int	status;

	if (type == SET)
		status = last_status;
	return (status);
}

bool	gs_readline_interrupted(int type, bool readline_interrupted)
{
	static bool	interrupted;

	if (type == SET)
		interrupted = readline_interrupted;
	return (interrupted);
}

bool	gs_syntax_error(int type, bool syntax_error)
{
	static bool	error;

	if (type == SET)
		error = syntax_error;
	return (error);
}

t_map	*gs_env(int type, t_map *(*set_map)(void))
{
	static t_map	*environ;

	if (type == SET)
		environ = set_map();
	return (environ);
}
