/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:07:16 by yotsubo           #+#    #+#             */
/*   Updated: 2024/11/18 15:16:08 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_node *node)
{
	int		status;
	char	**argv;

	do_redirect(node->command->redirects);
	argv = token_list_to_argv(node->command->args);
	if (ft_strncmp(argv[0], "exit", ft_strlen("exit")) == 0)
		status = builtin_exit(argv);
	/*
		TODO: exit以外のbuiltin
	*/
	// TODO: argvのfree
	reset_redirect(node->command->redirects);
	return (status);
}

t_bool	is_builtin(t_node *node)
{
	const char	*cmd_name;
	char		*builtin_commands[] = {"exit"};
	size_t		i;

	if (node == NULL || node->command == NULL || node->command->args == NULL \
		|| node->command->args->word == NULL)
		return (FALSE);
	cmd_name = node->command->args->word;
	i = 0;
	while (i < sizeof(builtin_commands) / sizeof(*builtin_commands))
	{
		if (ft_strncmp(cmd_name, builtin_commands[i], ft_strlen(builtin_commands[i])) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}