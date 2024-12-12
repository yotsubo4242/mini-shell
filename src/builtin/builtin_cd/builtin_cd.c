/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:33:16 by yotsubo           #+#    #+#             */
/*   Updated: 2024/12/12 18:14:37 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_oldpwd(bool *is_unset_pwd_p)
{
	char	*oldpwd;

	oldpwd = map_get(gs_env(GET, NULL), "PWD");
	if (oldpwd == NULL)
	{
		*is_unset_pwd_p = true;
		oldpwd = xstrdup(getcwd(NULL, PATH_MAX + 1));
	}
	return (oldpwd);
}

static int	append_home_path(char *path)
{
	char	*home;

	home = map_get(gs_env(GET, NULL), "HOME");
	if (home == NULL)
	{
		xperror2("cd", "HOME not set");
		return (1);
	}
	ft_strlcpy(path, home, PATH_MAX + 1);
	return (0);
}

static void	update_pwds(bool is_unset_pwd, char *oldpwd, char *newpwd)
{
	if (is_unset_pwd)
	{
		map_set(gs_env(GET, NULL), "PWD", newpwd, true);
		map_set(gs_env(GET, NULL), "OLDPWD", NULL, true);
		free(oldpwd);
	}
	else
	{
		map_set(gs_env(GET, NULL), "PWD", newpwd, false);
		map_set(gs_env(GET, NULL), "OLDPWD", oldpwd, true);
	}
}

int	builtin_cd(char **argv)
{
	char	*oldpwd;
	char	path[PATH_MAX + 1];
	char	*newpwd;
	bool	is_unset_pwd;

	is_unset_pwd = false;
	oldpwd = get_oldpwd(&is_unset_pwd);
	if (argv[1] == NULL)
	{
		if (append_home_path(path) > 0)
			return (1);
	}
	else
		ft_strlcpy(path, argv[1], PATH_MAX + 1);
	if (chdir(path) < 0)
	{
		xperror3("cd", path, NULL);
		return (1);
	}
	newpwd = resolve_pwd(oldpwd, path);
	update_pwds(is_unset_pwd, oldpwd, newpwd);
	free(newpwd);
	return (0);
}
