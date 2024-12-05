/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 01:47:03 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/12/05 16:53:25 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_map	*g_env = NULL;
bool	g_syntax_error = FALSE;
int	g_last_status = 0;
volatile sig_atomic_t	g_sig = 0;
bool	g_readline_interrupted = false;

void	interpret(char *line, int *stat_loc)
{
	t_token *tok;
	t_node	*node;

	tok = tokenize(line);
	if (at_eof(tok))
		;
	else if (g_syntax_error)
		*stat_loc = ERROR_TOKENIZE;
	else 
	{
		node = parse(tok);
		if (g_syntax_error)
			*stat_loc = ERROR_PARSE;
		else 
		{
			expand(node);
			*stat_loc = exec(node);
		}
		free_node(node);
	}
	free_tok(tok);
}

int	main(void)
{
	char	*line;

	g_env = init_env();
	setup_signal();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		interpret(line, &g_last_status);
		free(line);
	}
	builtin_exit(NULL);
}
