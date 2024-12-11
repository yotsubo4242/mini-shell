/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 01:47:03 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/12/05 17:34:54 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

void	interpret(char *line)
{
	t_token	*tok;
	t_node	*node;

	tok = tokenize(line);
	if (at_eof(tok))
		;
	else if (gs_syntax_error(GET, TRUE))
		gs_last_status(SET, ERROR_TOKENIZE);
	else
	{
		node = parse(tok);
		if (gs_syntax_error(GET, TRUE))
			gs_last_status(SET, ERROR_PARSE);
		else
		{
			expand(node);
			gs_last_status(SET, exec(node));
		}
		free_node(node);
	}
	free_tok(tok);
}

int	main(void)
{
	char	*line;

	gs_env(SET, init_env);
	gs_last_status(SET, 0);
	gs_syntax_error(SET, FALSE);
	setup_signal();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		interpret(line);
		free(line);
	}
	builtin_exit(NULL);
}
