/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:07:16 by yotsubo           #+#    #+#             */
/*   Updated: 2024/12/13 16:22:49 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_node *node)
{
	int		status;
	char	**argv;

	status = 0;
	do_redirect(node->command->redirects);
	argv = token_list_to_argv(node->command->args);
	if (ft_strcmp(argv[0], "exit") == 0)
		status = builtin_exit(argv);
	else if (ft_strcmp(argv[0], "export") == 0)
		status = builtin_export(argv);
	else if (ft_strcmp(argv[0], "unset") == 0)
		status = builtin_unset(argv);
	else if (ft_strcmp(argv[0], "env") == 0)
		status = builtin_env(argv);
	else if (ft_strcmp(argv[0], "cd") == 0)
		status = builtin_cd(argv);
	else if (ft_strcmp(argv[0], "echo") == 0)
		status = builtin_echo(argv);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		status = builtin_pwd(argv);
	reset_redirect(node->command->redirects);
	free_argv(argv);
	return (status);
}

static int	is_builtin_exit(int res, char **builtin_commands)
{
	free_char_arys(builtin_commands);
	return (res);
}

static char	**make_builtin_commands_ary(void)
{
	char	**builtin_commands;

	builtin_commands = xcalloc(8, sizeof(char *));
	builtin_commands[0] = xstrdup("exit");
	builtin_commands[1] = xstrdup("export");
	builtin_commands[2] = xstrdup("unset");
	builtin_commands[3] = xstrdup("env");
	builtin_commands[4] = xstrdup("echo");
	builtin_commands[5] = xstrdup("cd");
	builtin_commands[6] = xstrdup("pwd");
	return (builtin_commands);
}

bool	is_builtin(t_node *node)
{
	const char	*cmd_name;
	char		**builtin_commands;
	size_t		i;

	builtin_commands = make_builtin_commands_ary();
	if (node == NULL || node->command == NULL || node->command->args == NULL \
		|| node->command->args->word == NULL)
		return (is_builtin_exit(false, NULL));
	cmd_name = node->command->args->word;
	i = 0;
	while (builtin_commands[i])
	{
		if (!ft_strcmp(cmd_name, builtin_commands[i]))
			return (is_builtin_exit(true, builtin_commands));
		i++;
	}
	return (is_builtin_exit(false, builtin_commands));
}
