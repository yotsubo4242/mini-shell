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

void	fatal_error(const char *msg) __attribute__((noreturn));

bool	is_directory(const char *path)
{
	struct stat	buf;

	if (stat(path, &buf) < 0)
	{
		return (false);
	}
	return (S_ISDIR(buf.st_mode));
}

static bool	is_dot_path(const char *filename)
{
	if (ft_strcmp(filename, ".") == 0 || ft_strcmp(filename, "..") == 0)
		return (true);
	return (false);
}

char	*search_path(const char *filename)
{
	char	path[PATH_MAX];
	char	*value;
	char	*end;
	bool	is_permission_denied;

	// error handling: filename is "." or ".."
	is_permission_denied = false;
	if (*filename == '\0')
		return (xstrdup(""));
	if (is_dot_path(filename))
		return (NULL);
	value = map_get(gs_env(GET, NULL), "PATH");
	if (!value)
		return (NULL);
	while (*value)
	{
		ft_bzero(path, PATH_MAX);
		end = ft_strchr(value, ':');
		if (end)
			ft_strlcpy(path, value, end - value + 1);
		else
			ft_strlcpy(path, value, PATH_MAX);
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, filename, PATH_MAX);
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) < 0)
			{
				is_permission_denied = true;
				if (end == NULL)
					break ;
				value = end + 1;
				continue ;
			}
			char	*dup;

			dup = xstrdup(path);
			return (dup);
		}
		if (end == NULL)
			return (NULL);
		value = end + 1;
	}
	if (is_permission_denied)
		err_exit(filename, "Permission denied", 126);
	return (NULL);
}
