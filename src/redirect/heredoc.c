/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkitahar <tkitahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 13:49:22 by tkitahar          #+#    #+#             */
/*   Updated: 2024/12/07 13:49:48 by tkitahar         ###   ########.fr       */
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
		line = readline("> ");
		if (line == NULL)
		{
			// TODO: ↓readlineが何回inputを受け取ったのかをでっかい構造体で保持して, ここで表示する.
			ft_dprintf(STDERR_FILENO, "bash: warning: here-document at line %d delimited by end-of-file (wanted `EOF')\n", 1);
			break ;
		}
		if (g_readline_interrupted)
		{
			free(line);
			break ;
		}
		if (!ft_strcmp(line, delimiter))
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
