/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:33:16 by yotsubo           #+#    #+#             */
/*   Updated: 2024/11/23 02:22:07 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*resolve(char *oldpwd, char *path)
{
	
}

int	builtin_cd(char **argv)
{
	char	*home;
	char	*oldpwd;
	char	path[PATH_MAX];
	char	*newpwd;

	oldpwd = map_get(g_env, "PWD");
	map_set(g_env, "OLDPWD", oldpwd);
	if (argv[1] == NULL)
	{
		home = map_get(g_env, "HOME");
		if (home == NULL)
		{
			ft_dprintf(STDERR_FILENO, "cd: HOME not set\n");
			return (1);
		}
		ft_strlcpy(path, home, PATH_MAX);
	}
	else
		ft_strlcpy(path, argv[1], PATH_MAX);
	if (chdir(path) < 0)
	{
		ft_dprintf(STDERR_FILENO, "cd: chdir\n");
		return (1);
	}
	newpwd = resolve_pwd(oldpwd, path);
	map_set(g_env, "PWD", newpwd);
	free(newpwd);
	return (0);
}
