/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 02:34:47 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/11/09 16:47:20 by yuotsubo         ###   ########.fr       */
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

// char	**make_options(t_token *tok)
// {
// 	char	**cmd_with_opt;
// 	size_t	param_num;
// 	size_t	i;

// 	param_num = get_param_num(tok);
// 	cmd_with_opt = (char **)malloc(sizeof(char *) * (param_num + 1));
// 	if (!cmd_with_opt)
// 		return (NULL);
// 	i = 0;
// 	while (i < param_num)
// 	{
// 		cmd_with_opt[i++] = tok->word;
// 		tok = tok->next;
// 	}
// 	cmd_with_opt[i] = NULL;
// 	return (cmd_with_opt);
// }

// int	interpret(t_node *node)
// {
// 	extern char	**environ;
// 	char		**cmd_with_opt;
// 	pid_t		pid;
// 	int			wstatus;
// 	char		*cmd;

// 	pid = fork();
// 	if (pid < 0)
// 		fatal_error("fork");
// 	else if (!pid)
// 	{
// 		// child process
// 		cmd = search_path(node->args->word);
// 		if (!cmd)
// 			fatal_error("command not found");
// 		cmd_with_opt = make_options(node->args);
// 		execve(cmd, cmd_with_opt, environ);
// 		fatal_error("execve");
// 	} else {
// 		// parent process
// 		wait(&wstatus);
// 		return (WEXITSTATUS(wstatus));
// 	}
// }


// 宇佐美さんのpipeline時点から引用.

// これは一旦自作.
void	err_exit(const char *name, const char *err_msg, int estatus)
{
	ft_printf("%s: %s\n", name, err_msg);
	exit(estatus);
}

static void	validate_access(const char *path, const char *filename)
{
	if (path == NULL)
		err_exit(filename, "command not found", 127);
	if (access(path, F_OK) < 0)
		err_exit(filename, "command not found", 127);
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

static char	**token_list_to_argv(t_token *tok)
{
	char	**argv;
	size_t	i;

	argv = ft_calloc(argv_len(tok) + 1, sizeof(char *));
	if (!argv)
		fatal_error("calloc");
	i = 0;
	while (tok && !at_eof(tok))
	{
		argv[i] = ft_strdup(tok->word);
		if (!argv[i])
			fatal_error("strdup");
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
		prepare_pipe_child(node);
		do_redirect(node->command->redirects);
		argv = token_list_to_argv(node->command->args);
		path = argv[0];
		if (ft_strchr(path, '/') == NULL)
			path = search_path(path);
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
			status = WEXITSTATUS(wstatus);
		else if (wait_result < 0)
		{
			if (errno == ECHILD)
				break ;
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
	last_pid = exec_pipeline(node);
	status = wait_pipeline(last_pid);
	return (status);
}