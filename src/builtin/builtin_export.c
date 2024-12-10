/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:15:23 by yotsubo           #+#    #+#             */
/*   Updated: 2024/12/10 11:41:24 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_allenv(void)
{
	t_item	*item;

	item = g_env->item_head.next;
	while (item)
	{
		if (item->value)
			ft_printf("declare -x %s=\"%s\"\n", item->key, item->value);
		else
			ft_printf("declare -x %s\n", item->key);
		item = item->next;
	}
}

int	builtin_export(char **argv)
{
	size_t	i;
	int		status;

	if (argv[1] == NULL)
	{
		print_allenv();
		return (0);
	}
	status = 0;
	i = 1;
	while (argv[i])
	{
		if (map_put(g_env, argv[i]) < 0)
		{
			ft_dprintf(STDERR_FILENO, "bash: export: `%s': not a valid identifier\n", argv[i]);
			status = 1;
		}
		i++;
	}
	return (status);
}
