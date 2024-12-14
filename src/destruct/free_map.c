/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:39:25 by yotsubo           #+#    #+#             */
/*   Updated: 2024/12/14 13:55:49 by yuotsubo         ###   ########.fr       */
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
	t_item	*item;

	if (map == NULL)
		return ;
	item = map->item_head.next;
	free_item(item);
	free(map);
	map = NULL;
}
