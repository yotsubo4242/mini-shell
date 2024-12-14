/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:13:44 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/12/12 18:15:45 by yuotsubo         ###   ########.fr       */
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

char	*resolve_pwd(char *oldpwd, char *path)
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
