/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 02:34:47 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/12/03 18:12:07 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	fatal_error(const char *msg)
{
	ft_dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
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

void	t_err_exit(const char *name, const char *err_msg, int estatus)
{
	ft_dprintf(STDERR_FILENO, "bash: %s: %s\n", name, err_msg);
	exit(estatus);
}

void	err_exit(const char *name, const char *err_msg, int estatus)
{
	ft_dprintf(STDERR_FILENO, "%s: %s\n", name, err_msg);
	exit(estatus);
}

static void	validate_access(const char *path, const char *filename)
{
	if (path == NULL)
		err_exit(filename, "command not found", 127);
	if (*path == '\0')
		err_exit("''", "command not found", 127);
	if (access(path, F_OK) < 0)
	{
		if (!ft_strcmp(path, filename))
			err_exit(filename, "No such file or directory", 127);
		else
			err_exit(filename, "command not found", 127);
	}
}

static size_t	argv_len(t_token *tok)
{
	size_t	len;

	len = 0;
	while (tok && !at_eof(tok))
	{
		len++;
		tok = tok->next;
	}
	return (len);
}

char	**token_list_to_argv(t_token *tok)
{
	char	**argv;
	size_t	i;

	argv = xcalloc(argv_len(tok) + 1, sizeof(char *));
	i = 0;
	while (tok && !at_eof(tok))
	{
		argv[i] = xstrdup(tok->word);
		i++;
		tok = tok->next;
	}
	return (argv);
}

static pid_t	exec_pipeline(t_node *node)
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
		// child process
		reset_signal();
		prepare_pipe_child(node);
		do_redirect(node->command->redirects);
		argv = token_list_to_argv(node->command->args);
		path = argv[0];
		// TODO: is a directoryのエラーステータス
		if (ft_strchr(path, '/') == NULL)
			path = search_path(path);
		else if (is_directory(path))
			err_exit(path, "Is a directory", 126);
		validate_access(path, argv[0]);
		execve(path, argv, environ);
		reset_redirect(node->command->redirects);
		fatal_error("execve");
	}
	// parent process
	prepare_pipe_parent(node);
	if (node->next)
		return (exec_pipeline(node->next));
	return (pid);
}

int	wait_pipeline(pid_t last_pid)
{
	pid_t	wait_result;
	int		status;
	int		wstatus;

	while (1)
	{
		wait_result = wait(&wstatus);
		if (wait_result == last_pid)
		{
			if (WIFSIGNALED(wstatus))
				status = 128 + WTERMSIG(wstatus);
			else
				status = WEXITSTATUS(wstatus);
		}
		else if (wait_result < 0)
		{
			if (errno == ECHILD)
				break ;
			else if (errno == EINTR)
				continue ;
			else
				fatal_error("wait");
		}
	}
	return (status);
}

int	exec(t_node *node)
{
	pid_t	last_pid;
	int		status;

	if (open_redir_file(node) < 0)
		return (ERROR_OPEN_REDIR);
	// TODO: pipeとbuiltinが一緒に使われてる時の挙動が若干不安.
	if (node->next == NULL && is_builtin(node))
		status = exec_builtin(node);
	else
	{
		last_pid = exec_pipeline(node);
		status = wait_pipeline(last_pid);
	}
	return (status);
}
