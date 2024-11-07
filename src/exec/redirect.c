/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:56:42 by yotsubo           #+#    #+#             */
/*   Updated: 2024/11/07 18:16:09 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_heredoc(const char *delimiter)
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
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		dprintf(pfd[1], "%s\n", line);
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
		node->filefd = open(node->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (node->kind == ND_REDIR_IN)
		node->kind = opne(node->filename, O_RDONLY);
	else if (node->kind == ND_REDIR_APPEND)
		node->filefd = open(node->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (node->kind == ND_REDIR_HEREDOC)
		node->filefd = read_heredoc(node->delimiter->word);
	// if (node->filefd < 0)
	// {
	// 	// TODO: ファイルが開けなかったときの処理
	// }
	return (open_redir_file(node->next));
}