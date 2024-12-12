/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:08:02 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/12/03 19:34:39 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_directory(const char *path)
{
	struct stat	buf;

	if (stat(path, &buf) < 0)
		return (false);
	return (S_ISDIR(buf.st_mode));
}

static bool	is_dot_path(const char *filename)
{
	if (ft_strcmp(filename, ".") == 0 || ft_strcmp(filename, "..") == 0)
		return (true);
	return (false);
}

char	*prepare_path(char *path, char *end, char *value, const char *filename)
{
	ft_bzero(path, PATH_MAX);
	end = ft_strchr(value, ':');
	if (!end)
		ft_strlcpy(path, value, PATH_MAX);
	ft_strlcpy(path, value, end - value + 1);
	ft_strlcat(path, "/", PATH_MAX);
	ft_strlcat(path, filename, PATH_MAX);
	return (end);
}

char	*do_serch_path(char *value, char *path, const char *filename)
{	
	bool	is_permission_denied;
	char	*dup;
	char	*end;

	while (*value)
	{
		end = prepare_path(path, end, value, filename);
		if (access(path, F_OK) != 0)
		{
			if (end == NULL)
				return (NULL);
			value = end + 1;
		}
		if (access(path, X_OK) >= 0)
		{
			dup = xstrdup(path);
			return (dup);
		}
		is_permission_denied = true;
		if (end == NULL)
			break ;
		value = end + 1;
		continue ;
	}
	if (is_permission_denied)
		err_exit(filename, "Permission denied", 126);
	return (NULL);
}

char	*search_path(const char *filename)
{
	char	path[PATH_MAX];
	char	*value;

	if (*filename == '\0')
		return (xstrdup(""));
	if (is_dot_path(filename))
		return (NULL);
	value = map_get(gs_env(GET, NULL), "PATH");
	if (!value)
		return (NULL);
	return (do_serch_path(value, path, filename));
}
