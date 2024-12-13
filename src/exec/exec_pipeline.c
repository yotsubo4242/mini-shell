/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkitahar <tkitahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:54:23 by tkitahar          #+#    #+#             */
/*   Updated: 2024/12/13 15:54:59 by tkitahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	exec_pipeline(t_node *node)
{
	extern char	**environ;
	char		*path;
	pid_t		pid;
	char		**argv;

	if (!node)
		return (-1);
	prepare_pipe(node);
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
		reset_signal();
		prepare_pipe_child(node);
		if (is_builtin(node))
			exit(exec_builtin(node));
		do_redirect(node->command->redirects);
		argv = token_list_to_argv(node->command->args);
		path = argv[0];
		if (ft_strchr(path, '/') == NULL)
			path = search_path(path);
		else if (is_directory(path))
			err_exit(path, "Is a directory", 126);
		validate_access(path, argv[0]);
		execve(path, argv, environ);
		reset_redirect(node->command->redirects);
		fatal_error("execve");
	}
	prepare_pipe_parent(node);
	if (node->next)
		return (exec_pipeline(node->next));
	return (pid);
}

