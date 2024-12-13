/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:33:25 by yotsubo           #+#    #+#             */
/*   Updated: 2024/12/12 19:45:15 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_map	*map_new(void)
{
	t_map	*map;

	map = (t_map *)xmalloc(sizeof(t_map));
	map->item_head.key = NULL;
	map->item_head.value = NULL;
	map->item_head.next = NULL;
	return (map);
}

char	*map_get(t_map *map, const char *key)
{
	t_item	*item;

	item = map->item_head.next;
	while (item != NULL)
	{
		if (!ft_strcmp(key, item->key))
			return (item->value);
		item = item->next;
	}
	return (NULL);
}

int	map_set(t_map *map, const char *key, const char *value, bool should_free)
{
	t_item	*item;

	if (key == NULL || !is_identifier(key))
		return (-1);
	item = map->item_head.next;
	while (item != NULL)
	{
		if (!ft_strcmp(key, item->key))
			break ;
		item = item->next;
	}
	if (item != NULL)
		item_update(item, value, should_free);
	else
		item_apend_acending(key, value);
	return (0);
}

int	map_put(t_map *map, const char *str)
{
	int		res;
	char	*key_end;
	char	*key;
	char	*value;

	key_end = ft_strchr(str, '=');
	if (key_end == NULL)
	{
		key = xstrdup(str);
		value = NULL;
	}
	else
	{
		key = ft_substr(str, 0, key_end - str);
		value = ft_substr(str, key_end - str + 1, ft_strlen(str));
		if (key == NULL || value == NULL)
			fatal_error("substr");
	}
	res = map_set(map, key, value, true);
	free(key);
	free(value);
	return (res);
}

int	map_unset(t_map *map, const char *key)
{
	t_item	*item;
	t_item	*prev;

	if (key == NULL || !is_identifier(key))
		return (-1);
	item = map->item_head.next;
	prev = &(map->item_head);
	while (item != NULL)
	{
		if (!ft_strcmp(key, item->key))
		{
			prev->next = item->next;
			free(item->key);
			free(item->value);
			free(item);
			return (0);
		}
		prev = item;
		item = item->next;
	}
	return (0);
}
