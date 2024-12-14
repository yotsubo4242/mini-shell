/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:54:23 by tkitahar          #+#    #+#             */
/*   Updated: 2024/12/14 11:45:58 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pipe_child(t_node *node)
{
	char		**argv;
	char		*path;
	extern char	**environ;

	reset_signal();
	prepare_pipe_child(node);
	if (is_builtin(node))
		exit(exec_builtin(node));
	do_redirect(node->command->redirects);
	if (node->command->args == NULL)
		exit(0);
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

pid_t	exec_pipeline(t_node *node)
{
	pid_t		pid;

	if (!node)
		return (-1);
	prepare_pipe(node);
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
		exec_pipe_child(node);
	prepare_pipe_parent(node);
	if (node->next)
		return (exec_pipeline(node->next));
	return (pid);
}
