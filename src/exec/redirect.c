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

	if (pipe(pfd) < 0)
		fatal_error("pipe");
	while (1)
	{
		line = readline(">");
		if (line == NULL)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		if (is_delim_unquoted)
			line = expand_heardoc_line(line);
		ft_dprintf(pfd[1], "%s\n", line);
		free(line);
	}
	close(pfd[1]);
	return (pfd[0]);
}

int	open_redir_file(t_node *node)
{
	// 終了条件
	if (node == NULL)
		return (0);
	// ND_PIIPELINEなら, そこに入っているcommandで
	// open_redir_file()を行い, pipe挟んで右に移動する.
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
	// if (node->filefd < 0)
	// {
	// 	// TODO: ファイルが開けなかったときの処理
	// }
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
		dup2(redir->filefd, redir->targetfd);
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
		close(redir->filefd);
		close(redir->targetfd);
		// ↓↑stashの処理無いから変わるかも. 
		// dpu2(redir->stashed_targetfd, redir->targetfd)
	}
	else
		assert_error("reset_redirect");
}
