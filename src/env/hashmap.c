/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:33:25 by yotsubo           #+#    #+#             */
/*   Updated: 2024/11/14 07:27:39 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

// cleanup関数群
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

// new関数群
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

// map_get
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

// map_set関数群
t_bool	is_alpha_under(char c)
{
	return (c == '_' || ft_isalpha(c));
}

t_bool	is_alnum_under(char c)
{
	return (is_alpha_under(c) || ft_isdigit(c));
}

t_bool	is_identifier(const char *str)
{
	size_t	i;

	i = 0;
	if (!is_alpha_under(str[i]))
		return (FALSE);
	i++;
	while (str[i])
	{
		if (!is_alnum_under(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	item_update(t_item *item, const char *value)
{
	free(item->value);
	if (value == NULL)
		item->value = NULL;
	else
	{
		item->value = ft_strdup(value);
		if (item->value == NULL)
			fatal_error ("strdup");
	}
}

t_item	*item_apend(t_item *item, const char *key, const char *value)
{
	t_item	*item;

	if (value == NULL)
	{
		item = item_new(ft_strdup(key), NULL);
		if (item->key == NULL)
			fatal_error("strdup");
	} else {
		item = item_new(ft_strdup(key), ft_strdup(value));
		if (item->key == NULL || item->value == NULL)
			fatal_error ("strdup");
	}
	return (item);
}

// keyとvalueを元に, mapの(更新 || 追加)を行う関数. 
// keyが存在していれば更新, 存在していなければ追加を行う. 
// 処理が正常に終わったときは0, エラーの時は-1を返す. 
// エラー：keyがNULLか環境変数のの命名規則に合っていないもの.
int	map_set(t_map *map, const char *key, const char *value)
{
	t_item	*item;
	t_item	*prev;

	if (key == NULL || !is_identifier(key))
		return (-1);
	item = map->item_head.next;
	while (item != NULL)
	{
		if (!ft_strncmp(key, item->key, ft_strlen(key)))
			break ;
		prev = item;
		item = item->next;
	}
	if (item != NULL)
		item_update(item, value);
	else
		prev->next = item_apend(item, key, value);
	return (0);
}
