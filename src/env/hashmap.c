/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:33:25 by yotsubo           #+#    #+#             */
/*   Updated: 2024/11/14 07:01:15 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

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

// mapのinit用関数. item_headのkey, valueはNULLにしておく.
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

// keyに対応するvalueを得る関数. 戻り値は辞書上のvalueのアドレス. 
// 辞書にkeyが存在しない場合はNULLを返す.  
// 一旦NULLガードはしないので, 呼び出し元でmap, keyの存在は保証する. 
char	*map_get(t_map *map, const char *key)
{
	t_item	*item;
	char	*res;

	item = map->item_head.next;
	while (item != NULL)
	{
		if (!ft_strncmp(key, item->key, ft_strlen(key)))
			return (item->value);
		item = item->next;
	}
	return (NULL);
}
