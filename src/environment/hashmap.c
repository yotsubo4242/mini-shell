/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:33:25 by yotsubo           #+#    #+#             */
/*   Updated: 2024/11/14 00:46:52 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"

void	cleanup_item(t_item *item)
{
	if (item == NULL)
		return ;
	if (item->key != NULL)
		free(item->key);
	if (item->value != NULL)
		free(item->value);
	free(item);
}

void	cleanup_items(t_item *item)
{
	if (item == NULL)
		return ;
	cleanup_item(item);
	cleanup_items(item->next);
}

void	cleanup_map(t_map *map)
{
	if (map == NULL)
		return ;
	cleanup_items(map->item_head.next);
	free(map);
}

// 渡されてきたkey, valueはdupしてitemの中に格納する. 
t_item	*item_new(char *key, char *value)
{
	t_item	*item;

	item = (t_item *)ft_calloc(sizeof(t_item), 1);
	if (item == NULL)
		fatal_error("calloc");
	item->key = ft_strdup(key);
	if (item->key == NULL)
		fatal_error("strdup");
	item->value = ft_strdup(value);
	if (item->value == NULL)
		fatal_error("strdup");
	return (item);
}

t_map *map_new(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (map == NULL)
		fatal_error("malloc");
	map->item_head.key = NULL;
	map->item_head.value = NULL;
	map->item_head.next = NULL;
	return (map);
}
