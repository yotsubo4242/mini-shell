/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 02:34:47 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/10/16 00:36:11 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	fatal_error(const char *msg)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
	exit(EXIT_FAILURE);
}

size_t	get_param_num(t_token *tok)
{
	size_t	param_num;

	param_num = 0;
	while (tok)
	{
		tok = tok->next;
		param_num++;
	}
	return (param_num);
}

char	**make_options(t_token *tok)
{
	char	**cmd_with_opt;
	size_t	param_num;
	size_t	i;

	param_num = get_param_num(tok);
	cmd_with_opt = (char **)malloc(sizeof(char *) * (param_num + 1));
	if (!cmd_with_opt)
		return (NULL);
	i = 0;
	while (i < param_num)
	{
		cmd_with_opt[i++] = tok->word;
		tok = tok->next;
	}
	cmd_with_opt[i] = NULL;
	return (cmd_with_opt);
}

int	interpret(t_node *node)
{
	extern char	**environ;
	char		**cmd_with_opt;
	pid_t		pid;
	int			wstatus;
	char		*cmd;

	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (!pid)
	{
		// child process
		cmd = search_path(node->args->word);
		if (!cmd)
			fatal_error("command not found");
		cmd_with_opt = make_options(node->args);
		execve(cmd, cmd_with_opt, environ);
		fatal_error("execve");
	} else {
		// parent process
		wait(&wstatus);
		return (WEXITSTATUS(wstatus));
	}
}