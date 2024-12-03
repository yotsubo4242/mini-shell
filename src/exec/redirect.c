/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:56:42 by yotsubo           #+#    #+#             */
/*   Updated: 2024/11/13 16:36:20 by tkitahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	read_heredoc(const char *delimiter, bool is_delim_unquoted)
{
	char	*line;
	int		pfd[2];

	xpipe(pfd);
	g_readline_interrupted = false;
	while (1)
	{

		line = readline(">");
		if (line == NULL)
			break ;
		if (g_readline_interrupted)
		{
			free(line);
			break ;
		}
		if (ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		if (is_delim_unquoted)
			line = expand_heardoc_line(line);
		ft_dprintf(pfd[1], "%s\n", line);
		free(line);
	}
	xclose(pfd[1]);
	if (g_readline_interrupted)
	{
		xclose(pfd[0]);
		return (-1);
	}
	return (pfd[0]);
}

int	open_redir_file(t_node *node)
{
	if (node == NULL)
		return (0);
	if (node->kind == ND_PIPELINE)
	{
		if (open_redir_file(node->command) < 0)
			return (-1);
		if (open_redir_file(node->next) < 0)
			return (-1);
		return (0);
	}
	else if (node->kind == ND_SIMPLE_CMD)
		return (open_redir_file(node->redirects));
	else if (node->kind == ND_REDIR_OUT)
		node->filefd = open(node->filename->word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (node->kind == ND_REDIR_IN)
		node->filefd = open(node->filename->word, O_RDONLY);
	else if (node->kind == ND_REDIR_APPEND)
		node->filefd = open(node->filename->word, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (node->kind == ND_REDIR_HEREDOC)
		node->filefd = read_heredoc(node->delimiter->word, node->is_delim_unquoted);
	else
		assert_error("open_redir_file");
	// todo make xperror
	if (node->filefd < 0)
	{
		if (node->kind == ND_REDIR_OUT || node->kind == ND_REDIR_IN || node->kind == ND_REDIR_APPEND || node->kind == ND_REDIR_HEREDOC)
	// 		xperror();
			return (-1);
	}
	return (open_redir_file(node->next));
}

bool	is_redirect(t_node *node)
{
	if (node->kind == ND_REDIR_OUT)
		return (TRUE);
	else if (node->kind == ND_REDIR_IN)
		return (TRUE);
	else if (node->kind == ND_REDIR_APPEND)
		return (TRUE);
	else if (node->kind == ND_REDIR_HEREDOC)
		return (TRUE);
	return (FALSE);
}

void	do_redirect(t_node *redir)
{
	if (redir == NULL)
		return ;
	if (is_redirect(redir))
		xdup2(redir->filefd, redir->targetfd);
	else
		assert_error("do_redirect");
	do_redirect(redir->next);
}

void	reset_redirect(t_node *redir)
{
	if (redir == NULL)
		return ;
	reset_redirect(redir->next);
	if (is_redirect(redir))
	{
		xclose(redir->filefd);
		xclose(redir->targetfd);
		// ↓↑stashの処理無いから変わるかも. 
		// dpu2(redir->stashed_targetfd, redir->targetfd)
	}
	else
		assert_error("reset_redirect");
}
