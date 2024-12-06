/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:31:05 by yotsubo           #+#    #+#             */
/*   Updated: 2024/12/06 15:57:57 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#ifndef PATH_MAX
# define PATH_MAX 100
#endif

// warning: この関数もしかしたらバグの原因になりうる. 
// TODO: init_envの整形. 
t_map	*init_env(void)
{
	extern char	**environ;
	int			res;
	size_t		i;
	char		cwd[PATH_MAX];

	g_env = map_new();
	i = 0;
	while (environ[i])
	{
		res = map_put(g_env, environ[i]);
		if (res < 0)
			fatal_error("map_put");
		i++;
	}
	if (map_get(g_env, "SHLVL") == NULL)
		map_set(g_env, "SHLVL", "1");
	if (map_get(g_env, "PWD") == NULL)
	{
		getcwd(cwd, PATH_MAX);
		map_set(g_env, "PWD", cwd);
	}
	if (map_get(g_env, "OLDPWD") == NULL)
		map_set(g_env, "OLDPWD", NULL);
	map_unset(g_env, "_");
	return (g_env);
}

size_t	map_len(t_map *map)
{
	size_t	len;
	t_item	*item;

	item = map->item_head.next;
	len = 0;
	while (item != NULL)
	{
		len++;
		item = item->next;
	}
	return (len);
}

// valueがから文字列の時はARG=など, valueがNULLの時はNULLを返す. 
char	*item_get_string(t_item *item)
{
	char	*res;
	size_t	size;

	if (item == NULL || item->key == NULL || item->value == NULL)
		return (NULL);
	size = ft_strlen(item->key) + ft_strlen(item->value) + 2;
	res = (char *)xmalloc(sizeof(char) * size);
	ft_strlcpy(res, item->key, size);
	ft_strlcat(res, "=", size);
	ft_strlcat(res, item->value, size);
	return (res);
}

char	**get_environ(t_map *envmap)
{
	size_t	i;
	size_t	size;
	char	**environ;
	t_item	*item;

	size = map_len(envmap) + 1;
	environ = (char **)xcalloc(sizeof(char *), size);
	i = 0;
	item = envmap->item_head.next;
	while (item != NULL)
	{
		if (item->value)
		{
			environ[i] = item_get_string(item);
			i++;
		}
		item = item->next;
	}
	return (environ);
}
