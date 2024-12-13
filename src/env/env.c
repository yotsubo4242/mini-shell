/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:31:05 by yotsubo           #+#    #+#             */
/*   Updated: 2024/12/12 18:36:19 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_map	*init_env(void)
{
	extern char	**environ;
	int			res;
	size_t		i;
	char		cwd[PATH_MAX + 1];

	gs_env(SET,map_new);
	i = 0;
	while (environ[i])
	{
		res = map_put(gs_env(GET, NULL), environ[i]);
		if (res < 0)
			fatal_error("map_put");
		i++;
	}
	if (map_get(gs_env(GET, NULL), "SHLVL") == NULL)
		map_set(gs_env(GET, NULL), "SHLVL", "1", true);
	if (map_get(gs_env(GET, NULL), "PWD") == NULL)
	{
		getcwd(cwd, PATH_MAX);
		map_set(gs_env(GET, NULL), "PWD", cwd, true);
	}
	if (map_get(gs_env(GET, NULL), "OLDPWD") == NULL)
		map_set(gs_env(GET, NULL), "OLDPWD", NULL, true);
	map_unset(gs_env(GET, NULL), "_");
	return (gs_env(GET, NULL));
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
