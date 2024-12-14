/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkitahar <tkitahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:42:18 by tkitahar          #+#    #+#             */
/*   Updated: 2024/12/13 15:44:32 by tkitahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	exec(t_node *node)
{
	pid_t	last_pid;

	if (open_redir_file(node) < 0)
		return (ERROR_OPEN_REDIR);
	if (node->next == NULL && is_builtin(node))
		return (exec_builtin(node));
	last_pid = exec_pipeline(node);
	return (wait_pipeline(last_pid));
}
