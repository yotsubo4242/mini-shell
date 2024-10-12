/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 02:34:47 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/10/13 03:42:01 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	fatal_error(const char *msg) __attribute__((noreturn));

void	fatal_error(const char *msg)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
	exit(EXIT_FAILURE);
}

int	interpret(char *line)
{
	extern char	**environ;
	char		*argv[] = {line, NULL};
	pid_t		pid;
	int			wstatus;
	char		*cmd;

	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (!pid)
	{
		// child process
		cmd = search_path(line);
		if (!cmd)
			fatal_error("command not found");
		execve(cmd, argv, environ);
		fatal_error("execve");
	} else {
		// parent process
		wait(&wstatus);
		return (WEXITSTATUS(wstatus));
	}
}