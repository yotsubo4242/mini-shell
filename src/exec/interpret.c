/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 02:34:47 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/12/13 14:01:32 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (access(path, X_OK) < 0)
		err_exit(filename, "Permission denied", 126);
}

static size_t	expanded_token_len(t_token *tok)
{
	size_t	len;
	size_t	i;
	bool	is_word_head;

	len = 0;
	i = 0;
	is_word_head = true;
	while (tok->word[i] != '\0')
	{
		if (ft_isspace(tok->word[i]))
			is_word_head = true;
		else if (is_word_head)
		{
			is_word_head = false;
			len++;
		}
		i++;
	}
	return (len);
}

static char	*dup_until_space(const char *s)
{
	size_t	len;
	size_t	i;
	char	*dup;

	len = 0;
	i = 0;
	while (s[i] != '\0' && !ft_isspace(s[i]))
	{
		len++;
		i++;
	}
	dup = xmalloc(len + 1);
	ft_strlcpy(dup, s, len + 1);
	return (dup);
}

static size_t	argv_len(t_token *tok)
{
	size_t	len;

	len = 0;
	while (tok && !at_eof(tok))
	{
		if (tok->is_expanded)
			len += expanded_token_len(tok);
		else
			len++;
		tok = tok->next;
	}
	return (len);
}

char	**token_list_to_argv(t_token *tok)
{
	char	**argv;
	size_t	i;
	size_t	j;
	bool	is_word_head;

	argv = xcalloc(argv_len(tok) + 1, sizeof(char *));
	i = 0;
	while (tok && !at_eof(tok))
	{
		if (tok->is_expanded)
		{
			is_word_head = true;
			j = 0;
			while (j < ft_strlen(tok->word))
			{
				if (ft_isspace(tok->word[j]))
					is_word_head = true;
				else if (is_word_head)
				{
					is_word_head = false;
					argv[i] = dup_until_space(tok->word + j);
					i++;
				}
				j++;
			}
		}
		else
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

	if (open_redir_file(node) < 0)
		return (ERROR_OPEN_REDIR);
	if (node->next == NULL && is_builtin(node))
		return (exec_builtin(node));
	last_pid = exec_pipeline(node);
	return (wait_pipeline(last_pid));
}
