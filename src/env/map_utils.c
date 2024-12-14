/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:44:55 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/12/14 13:13:32 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_item	*item_new(const char *key, const char *value)
{
	t_item	*item;

	item = (t_item *)xcalloc(sizeof(t_item), 1);
	item->key = xstrdup(key);
	if (value != NULL)
		item->value = xstrdup(value);
	return (item);
}

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

void	item_apend(const char *key, const char *value)
{
	t_item	*item;
	t_item	*new;

	item = &(gs_env(GET, NULL)->item_head);
	if (value == NULL)
		new = item_new(key, NULL);
	else
		new = item_new(key, value);
	if (item->next == NULL)
		item->next = new;
	else
	{
		while (item->next != NULL)
			item = item->next;
		item->next = new;
	}
}
