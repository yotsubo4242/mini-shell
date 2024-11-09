/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 01:47:03 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/11/09 18:01:02 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool	g_syntax_error = FALSE;

int	main(void)
{
	char	*line;
	t_token	*tok;
	t_node	*node;

	rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
		{
			add_history(line);
			tok = tokenize(line);
			node = parse(tok);
			if (!g_syntax_error)
			{
				node = expand(node);
				exec(node);
			}
		}
		free(line);
	}
	exit(EXIT_SUCCESS);
}