/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:33:25 by yotsubo           #+#    #+#             */
/*   Updated: 2024/12/09 13:34:57 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	item = (t_item *)xcalloc(sizeof(t_item), 1);
	item->key = xstrdup(key);
	if (value != NULL)
		item->value = xstrdup(value);
	return (item);
}

// mapのinit用関数. item_headのkey, valueはNULLにしておく.
t_map *map_new(void)
{
	t_map	*map;

	map = (t_map *)xmalloc(sizeof(t_map));
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

	item = map->item_head.next;
	while (item != NULL)
	{
		if (!ft_strcmp(key, item->key))
			return (item->value);
		item = item->next;
	}
	return (NULL);
}

// map_set関数群
bool	is_identifier(const char *str)
{
	size_t	i;

	i = 0;
	if (!is_alpha_under(str[i]))
		return (false);
	i++;
	while (str[i])
	{
		if (!is_alpha_num_under(str[i]))
			return (false);
		i++;
	}
	return (true);
}

void	item_update(t_item *item, const char *value, bool should_free)
{
	if (should_free)
		free(item->value);
	if (value == NULL)
		item->value = NULL;
	else
		item->value = xstrdup(value);
}

void	item_apend_acending(const char *key, const char *value)
{
	t_item	*item;
	t_item	*new;
	t_item	*prev;

	item = &(sg_env(GET, NULL)->item_head);
	if (value == NULL)
		new = item_new(xstrdup(key), NULL);
	else
		new = item_new(xstrdup(key), xstrdup(value));
	if (item->next == NULL)
		item->next = new;
	else {
		prev = item;
		item = item->next;
		while (item != NULL && ft_strcmp(key, item->key) > 0)
		{
			prev = item;
			item = item->next;
		}
		prev->next = new;
		new->next = item;
	}
}

// keyとvalueを元に, mapの(更新 || 追加)を行う関数. 
// keyが存在していれば更新, 存在していなければ追加を行う. 
// 処理が正常に終わったときは0, エラーの時は-1を返す. 
// エラー：keyがNULLか環境変数のの命名規則に合っていないもの.
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
	// '='が含まれている場合(ARG=yeah) -> key:ARGにvalue:yeahを入れる.
	// '='が含まれていない場合(ARG) -> key:ARGにvalue:NULLを入れる.
	if (key_end == NULL)
	{
		key = xstrdup(str);
		value = NULL;
	} else {
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

// map_unset
// keyに対応するitemを削除する. 
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
