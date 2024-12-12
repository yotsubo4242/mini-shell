/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:15:23 by yotsubo           #+#    #+#             */
/*   Updated: 2024/12/12 18:12:59 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_allenv(void)
{
	t_item	*item;

	item = gs_env(GET, NULL)->item_head.next;
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
		if (map_put(gs_env(GET, NULL), argv[i]) < 0)
		{
			ft_dprintf(STDERR_FILENO, \
				"bash: export: `%s': not a valid identifier\n", argv[i]);
			status = 1;
		}
		i++;
	}
	return (status);
}
