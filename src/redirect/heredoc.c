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

void	do_read_heredoc(int pfd[2], const char *delimiter, \
									bool is_delim_unquoted)
{
	char	*line;

	gs_readline_interrupted(SET, FALSE);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ft_dprintf(STDERR_FILENO, "bash: warning: here-document at line %d delimited by \
					end-of-file (wanted `EOF')\n", 1);
			break ;
		}
		if (gs_readline_interrupted(GET, TRUE))
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
}

int	read_heredoc(const char *delimiter, bool is_delim_unquoted)
{
	int		pfd[2];

	xpipe(pfd);
	do_read_heredoc(pfd, delimiter, is_delim_unquoted);
	xclose(pfd[1]);
	if (gs_readline_interrupted(GET, TRUE))
	{
		xclose(pfd[0]);
		return (-1);
	}
	return (pfd[0]);
}
