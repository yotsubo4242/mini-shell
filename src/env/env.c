/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:31:05 by yotsubo           #+#    #+#             */
/*   Updated: 2024/11/14 17:38:56 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

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

int	main(void)
// {
// 	t_map	*map;

// 	map = init_env();
// 	output_map(map);
// 	return (0);
// }