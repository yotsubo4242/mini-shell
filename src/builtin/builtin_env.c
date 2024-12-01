/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:51:22 by yotsubo           #+#    #+#             */
/*   Updated: 2024/11/29 12:30:05 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(char **argv)
{
	t_item	*item;

	(void)argv;
	item = g_env->item_head.next;
	while (item)
	{
		if (item->value != NULL)
			ft_printf("%s=%s\n", item->key, item->value);
		item = item->next;
	}
	ft_printf("_=/usr/bin/env\n");
	return (0);
}
