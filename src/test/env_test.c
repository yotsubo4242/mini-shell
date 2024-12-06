/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:35:08 by yotsubo           #+#    #+#             */
/*   Updated: 2024/12/06 15:50:48 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fatal_error(const char *str)
{
	printf("ERROR: %s\n", str); fflush(stdout);
	exit(EXIT_FAILURE);
}

void	output_map(t_map *map)
{
	t_item	*item;

	item = map->item_head.next;
	while (item != NULL)
	{
		printf("key: %s, value: %s\n", item->key, item->value); fflush(stdout);
		item = item->next;
	}
}

int	main(void)
{
	t_map	*map;
	char	*value;
	int		res;

	map = map_new();
	if (!map)
		fatal_error("map_new");
	// map_set()によるkeyの追加.
	puts("\n--- map_set ---");
	res = map_set(map, "KEY", "value");
	if (res < 0)
		fatal_error("map_set");
	output_map(map);
	// map_get()による既存keyの検索. 
	puts("\n--- map_get ---");
	value = map_get(map, "KEY");
	if (value == NULL)
		fatal_error("map_get");
	printf("value: %s\n", value);
	// map_put()による新規keyの追加.
	puts("\n--- map_put ---");
	res = map_put(map, "KEY2=yeah");
	if (res < 0)
		fatal_error("map_put");
	output_map(map);
	// map_put()による既存keyの更新.
	puts("\n--- map_put ---");
	res = map_put(map, "KEY2=oh-my-god");
	if (res < 0)
		fatal_error("map_put");
	output_map(map);
	// map_unset()によるitemの削除.
	puts("\n--- map_unset ---");
	res = map_unset(map, "KEY2");
	if (res < 0)
		fatal_error("map_unset");
	output_map(map);
	cleanup_map(map);
	return (0);
}
