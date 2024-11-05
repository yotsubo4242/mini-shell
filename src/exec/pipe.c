/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:36:28 by yotsubo           #+#    #+#             */
/*   Updated: 2024/11/05 18:42:31 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_pipe(int dst[2], int src[2])
{
	dst[0] = src[1];
	dst[1] = src[0];
}

void	prepare_pipe(t_node *node)
{
	if (node == NULL)
		return ;
	if (pipe(node->outpipe) < 0)
		fatal_error("pipe");
	copy_pipe(node->next->inpipe, node->outpipe);
}

void	prepare_pipe_parent(t_node *node)
{
	if (node->inpipe[0] != STDIN_FILENO)
		close(node->inpipe[0]);
	if (node->next)
		close(node->outpipe[1]);
}
