/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 02:34:47 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/12/13 15:54:19 by tkitahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**token_list_to_argv(t_token *tok)
{
	char	**argv;
	size_t	i;
	size_t	j;
	bool	is_word_head;

	argv = xcalloc(argv_len(tok) + 1, sizeof(char *));
	i = 0;
	while (tok && !at_eof(tok))
	{
		if (tok->is_expanded)
		{
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
					i++;
				}
				j++;
			}
		}
		else
			argv[i] = xstrdup(tok->word);
		i++;
		tok = tok->next;
	}
	return (argv);
}
