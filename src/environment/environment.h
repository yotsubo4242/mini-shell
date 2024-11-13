/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:33:53 by yotsubo           #+#    #+#             */
/*   Updated: 2024/11/13 21:37:54 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

typedef struct s_item {
	char			*key;
	char			*value;
	struct s_item	*next;
}	t_item;

typedef struct s_map {
	t_item	item_head;
}	t_map;

t_item	*item_new(char *key, char *value);

t_map	*map_new(void);

char	*map_get(t_map *map, const char *key);

int		map_put(t_map *map, const char *string);

int		map_set(t_map *map, const char *key, const char *value);

int		map_unset(t_map *map, const char *key);

#endif