/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:36:28 by yotsubo           #+#    #+#             */
/*   Updated: 2024/11/09 17:05:41 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_pipe(int dst[2], int src[2])
{
	dst[0] = src[0];
	dst[1] = src[1];
}

void	prepare_pipe(t_node *node)
{
	if (node->next == NULL)
		return ;
	if (pipe(node->outpipe) < 0)
		fatal_error("pipe");
	copy_pipe(node->next->inpipe, node->outpipe);
}

void	prepare_pipe_child(t_node *node)
{
	xclose(node->outpipe[0]);
	xdup2(node->inpipe[0], STDIN_FILENO);
	xdup2(node->outpipe[1], STDOUT_FILENO);
}

void	prepare_pipe_parent(t_node *node)
{
	if (node->inpipe[0] != STDIN_FILENO)
		xclose(node->inpipe[0]);
	if (node->next)
		xclose(node->outpipe[1]);
}
