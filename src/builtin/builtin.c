/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:07:16 by yotsubo           #+#    #+#             */
/*   Updated: 2024/12/06 18:49:33 by yotsubo          ###   ########.fr       */
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
	// TODO: argvのfree
	reset_redirect(node->command->redirects);
	return (status);
}

bool	is_builtin(t_node *node)
{
	const char	*cmd_name;
	char		*builtin_commands[] = {"exit", "export", "unset", "env", "echo", "cd", "pwd"};
	size_t		i;

	if (node == NULL || node->command == NULL || node->command->args == NULL \
		|| node->command->args->word == NULL)
		return (false);
	cmd_name = node->command->args->word;
	i = 0;
	while (i < sizeof(builtin_commands) / sizeof(*builtin_commands))
	{
		if (!ft_strcmp(cmd_name, builtin_commands[i]))
			return (true);
		i++;
	}
	return (false);
}
