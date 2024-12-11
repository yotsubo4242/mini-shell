/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:39:25 by yotsubo           #+#    #+#             */
/*   Updated: 2024/12/11 22:39:34 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_item(t_item *item)
{
	if (item == NULL)
		return ;
	free(item->key);
	free(item->value);
	free_item(item->next);
	free(item);
	item = NULL;
}

void	free_map(t_map *map)
{
	t_item *item;

	if (map == NULL)
		return ;
	item = map->item_head.next;
	free_item(item->next);
	free(map);
	map = NULL;
}
