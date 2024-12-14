/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:15:23 by yotsubo           #+#    #+#             */
/*   Updated: 2024/12/14 14:01:05 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	item_apend_acending(const char *key, \
								const char *value, t_map *new_env)
{
	t_item	*item;
	t_item	*new;
	t_item	*prev;

	item = &(new_env->item_head);
	if (value == NULL)
		new = item_new(key, NULL);
	else
		new = item_new(key, value);
	if (item->next == NULL)
		item->next = new;
	else
	{
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

static t_map	*make_sort_env(t_map *env)
{
	t_map	*new_env;
	t_item	*item;

	new_env = map_new();
	item = env->item_head.next;
	while (item)
	{
		if (new_env->item_head.next == NULL)
			new_env->item_head.next = item_new(item->key, item->value);
		else
			item_apend_acending(item->key, item->value, new_env);
		item = item->next;
	}
	return (new_env);
}

static void	print_allenv(void)
{
	t_item	*item;
	t_map	*env;

	env = make_sort_env(gs_env(GET, NULL));
	item = env->item_head.next;
	while (item)
	{
		if (item->value)
			ft_printf("declare -x %s=\"%s\"\n", item->key, item->value);
		else
			ft_printf("declare -x %s\n", item->key);
		item = item->next;
	}
	free_map(env);
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
