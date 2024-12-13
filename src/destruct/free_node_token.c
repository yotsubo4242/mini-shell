/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_node_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:34:54 by tkitahar          #+#    #+#             */
/*   Updated: 2024/12/12 19:43:06 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_item(t_item *item)
{
	if (item == NULL)
		return ;
	if (item->key != NULL)
		free(item->key);
	if (item->value != NULL)
		free(item->value);
	free(item);
}

void	cleanup_items(t_item *item)
{
	if (item == NULL)
		return ;
	cleanup_item(item);
	cleanup_items(item->next);
}

void	cleanup_map(t_map *map)
{
	if (map == NULL)
		return ;
	cleanup_items(map->item_head.next);
	free(map);
}

void	free_char_arys(char **char_arys)
{
	size_t	i;

	i = 0;
	while (char_arys[i])
	{
		free(char_arys[i]);
		i++;
	}
	free(char_arys);
}

void	free_tok(t_token *tok)
{
	if (tok == NULL)
		return ;
	if (tok->word)
		free(tok->word);
	free_tok(tok->next);
	free(tok);
}

void	free_node(t_node *node)
{
	if (node == NULL)
		return ;
	free_tok(node->args);
	free_tok(node->filename);
	free_tok(node->delimiter);
	free_node(node->redirects);
	free_node(node->next);
	free_node(node->command);
	free(node);
}
