/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_to_argv.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 02:34:47 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/12/14 17:10:52 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dup_is_expanded(char **argv, size_t i, t_token *tok)
{
	bool	is_word_head;
	size_t	j;

	is_word_head = true;
	j = 0;
	while (j < ft_strlen(tok->word))
	{
		if (ft_isspace(tok->word[j]))
			is_word_head = true;
		else if (is_word_head)
		{
			is_word_head = false;
			argv[i] = dup_until_space(tok->word + j);
		}
		j++;
	}
	return (argv[i]);
}

char	**token_list_to_argv(t_token *tok)
{
	char	**argv;
	size_t	i;

	argv = xcalloc(argv_len(tok) + 1, sizeof(char *));
	i = 0;
	while (tok && !at_eof(tok))
	{
		argv[i] = xstrdup(tok->word);
		i++;
		tok = tok->next;
	}
	return (argv);
}
