/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:21:34 by tkitahar          #+#    #+#             */
/*   Updated: 2024/12/11 22:35:55 by yotsubo          ###   ########.fr       */
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
	static	bool	interrupted;

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

char *gs_line(int type, char *new_line)
{
	static	char * line;

	if (type == SET)
		line = new_line;
	return (line);
}
