/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:33:16 by yotsubo           #+#    #+#             */
/*   Updated: 2024/12/09 13:36:53 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	consume_path(char **rest, char *path, char *elm)
{
	size_t	elm_len;

	elm_len = ft_strlen(elm);
	if (ft_strncmp(path, elm, elm_len) == 0)
	{
		if (path[elm_len] == '\0' || path[elm_len] == '/')
		{
			*rest = path + elm_len;
			return (true);
		}
	}
	return (false);
}

static void	delete_last_elm(char *path)
{
	char	*start;
	char	*last_slash_per;

	start = path;
	last_slash_per = NULL;
	while (*path)
	{
		if (*path == '/')
			last_slash_per = path;
		path++;
	}
	// "PWD=/"の時は"cd ../"しても"PWD=/"のままになる
	if (last_slash_per != start)
		*last_slash_per = '\0';
}

static void	append_path_elm(char *dst, char **rest, char *src)
{
	size_t	elm_len;
	size_t	dst_len;

	elm_len = 0;
	while (src[elm_len] != '\0' && src[elm_len] != '/')
		elm_len++;
	dst_len = ft_strlen(dst);
	if (dst[dst_len - 1] != '/')
		ft_strlcat(dst, "/", PATH_MAX + 1);
	ft_strlcat(dst, src, dst_len + elm_len + 2);
	*rest = src + elm_len;
}

static char	*resolve_pwd(char *oldpwd, char *path)
{
	char	newpwd[PATH_MAX + 1];
	char	*dup;

	ft_bzero(newpwd, PATH_MAX + 1);
	if (oldpwd == NULL)
		return (NULL);
	if (*path == '/')
		ft_strlcpy(newpwd, "/", PATH_MAX);
	else
		ft_strlcpy(newpwd, oldpwd, PATH_MAX);
	while (*path)
	{
		if (*path == '/')
			path++;
		else if (consume_path(&path, path, "."))
			;
		else if (consume_path(&path, path, ".."))
			delete_last_elm(newpwd);
		else
			append_path_elm(newpwd, &path, path);
	}
	if (ft_strlen(newpwd) > 1 && newpwd[ft_strlen(newpwd) - 1] == '/')
		newpwd[ft_strlen(newpwd) - 1] = '\0';
	dup = xstrdup(newpwd);
	return (dup);
}

int	builtin_cd(char **argv)
{
	char	*home;
	char	*oldpwd;
	char	path[PATH_MAX + 1];
	char	*newpwd;
	bool	is_unset_pwd;

	is_unset_pwd = false;
	oldpwd = map_get(sg_env(GET, NULL), "PWD");
	if (oldpwd == NULL)
	{
		is_unset_pwd = true;
		oldpwd = xstrdup(getcwd(NULL, PATH_MAX + 1));
	}
	if (argv[1] == NULL)
	{
		home = map_get(sg_env(GET, NULL), "HOME");
		if (home == NULL)
		{
			xperror2("cd", "HOME not set");
			return (1);
		}
		ft_strlcpy(path, home, PATH_MAX + 1);
	}
	else
		ft_strlcpy(path, argv[1], PATH_MAX + 1);
	if (chdir(path) < 0)
	{
		xperror3("cd", path, NULL);
		return (1);
	}
	newpwd = resolve_pwd(oldpwd, path);
	if (is_unset_pwd)
	{
		map_set(sg_env(GET, NULL), "PWD", newpwd, true);
		map_set(sg_env(GET, NULL), "OLDPWD", NULL, true);
		free(oldpwd);
	}
	else
	{
		map_set(sg_env(GET, NULL), "PWD", newpwd, false);
		map_set(sg_env(GET, NULL), "OLDPWD", oldpwd, true);
	}
	free(newpwd);
	return (0);
}
