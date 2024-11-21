/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:20:12 by yotsubo           #+#    #+#             */
/*   Updated: 2024/11/21 14:28:10 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// unsetは変数の削除を行う. 
// 存在しない変数が指定されたときはエラー文は表示されない. 
// identifier以外の文字列が来た場合, エラー文が表示される. 
int	builitin_unset(char **argv)
{
	int		status;
	size_t	i;

	status = 0;
	i = 1;
	while (argv[i])
	{
		if (map_unset(g_env, argv[i]) < 0)
		{
			ft_dprintf(STDERR_FILENO, "unset: %s: not a valid identifier\n", argv[i]);
			status = 1;
		}
		else
			status = 0;
		i++;
	}
	return (status);
}
