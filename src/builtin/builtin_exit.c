/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:30:49 by yotsubo           #+#    #+#             */
/*   Updated: 2024/11/18 14:53:25 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 本番はグローバル変数として持てないからどうしよう...
int	last_status = 0;

void	builtin_error(const char *cmd_name, const char *msg)
{
	ft_dprintf(STDERR_FILENO, "%s: %s\n", cmd_name, msg);
}

int	builtin_exit(char **argv)
{
	long	res;

	// bash: 引数のエラーがあっても必ずexitする. (エラーの場合は終了ステータスが1に設定)
	// bash: exitするときは必ず"exit"と表示される. 
	ft_putstr_fd("exit", STDERR_FILENO);
	if (argv[1] == NULL)
		exit(last_status);
	if (argv[2])
	{
		builtin_error("exit", "too many arguments");
		exit(EXIT_FAILURE);
	}
}
