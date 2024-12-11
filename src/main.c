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

#include "macro.h"
#include "minishell.h"

bool g_readline_interrupted = FALSE;
volatile sig_atomic_t	g_sig = 0;

void	interpret(char *line)
{
	t_token *tok;
	t_node	*node;

	tok = tokenize(line);
	if (at_eof(tok))
		;
	else if (sg_syntax_error(GET, FALSE))
		sg_last_status(SET, ERROR_TOKENIZE);
	else 
	{
		node = parse(tok);
		if (sg_syntax_error(GET, FALSE))
			sg_last_status(SET, ERROR_PARSE);
		else 
		{
			expand(node);
			sg_last_status(SET, exec(node));
		}
		free_node(node);
	}
	free_tok(tok);
}

int	main(void)
{
	char	*line;

	sg_env(SET, init_env);
	sg_last_status(SET, 0);
	sg_syntax_error(SET, FALSE);
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
