/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 03:36:01 by yotsubo           #+#    #+#             */
/*   Updated: 2024/12/12 16:26:28 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	equal_inode(const char *path1, const char *path2)
{
	struct stat	st1;
	struct stat	st2;

	ft_bzero(&st1, sizeof(st1));
	ft_bzero(&st2, sizeof(st2));
	if (stat(path1, &st1) < 0)
		fatal_error("stat");
	if (stat(path2, &st2) < 0)
		fatal_error("stat");
	return (st1.st_ino == st2.st_ino);
}

// PWDには論理パスが入っている. 
// それがなかった場合or不適の場合にはgetcwd()を用いて物理パスを取得する. 
int	builtin_pwd(char **argv)
{
	char	*pwd;
	char	cwd[PATH_MAX + 1];

	(void)argv;
	pwd = map_get(gs_env(GET, NULL), "PWD");
	if (pwd == NULL || !equal_inode(pwd, "."))
	{
		if (getcwd(cwd, PATH_MAX) == NULL)
		{
			ft_dprintf(STDERR_FILENO, "pwd: getcwd\n");
			return (1);
		}
		ft_dprintf(STDOUT_FILENO, "%s\n", cwd);
		return (0);
	}
	else
	{
		ft_dprintf(STDOUT_FILENO, "%s\n", pwd);
		return (0);
	}
}
