/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:31:05 by yotsubo           #+#    #+#             */
/*   Updated: 2024/11/19 19:18:26 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	fatal_error(const char *str)
// {
// 	printf("ERROR: %s\n", str); fflush(stdout);
// 	exit(EXIT_FAILURE);
// }

// void	output_map(t_map *map)
// {
// 	t_item	*item;

// 	item = map->item_head.next;
// 	while (item != NULL)
// 	{
// 		printf("key: %s\n\tvalue: %s\n", item->key, item->value); fflush(stdout);
// 		item = item->next;
// 	}
// }

// void	output_env(char **env)
// {
// 	size_t	i;

// 	i = -1;
// 	while (env[++i])
// 		printf("%ld:\n\t%s\n", i, env[i]);
// }

t_map	*init_env(void)
{
	t_map		*map;
	extern char	**environ;
	int			res;
	size_t		i;

	map = map_new();
	i = 0;
	while (environ[i])
	{
		res = map_put(map, environ[i]);
		if (res < 0)
			fatal_error("map_put");
		i++;
	}
	return (map);
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
	res = (char *)malloc(sizeof(char) * size);
	if (res == NULL)
		fatal_error("malloc");
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
	environ = (char **)calloc(sizeof(char *), size);
	if (environ == NULL)
		fatal_error("calloc");
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

// int	main(void)
// {
// 	t_map	*map;
// 	char	**env;

// 	map = init_env();
// 	output_map(map);
// 	env = get_environ(map);
// 	output_env(env);
// 	return (0);
// }