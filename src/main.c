/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 01:47:03 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/12/14 14:45:04 by yuotsubo         ###   ########.fr       */
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
			if (gs_readline_interrupted(GET, TRUE))
				gs_last_status(SET, ERROR_SIGINT);
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
		gs_syntax_error(SET, FALSE);
	}
	builtin_exit(NULL);
}
