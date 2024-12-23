/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 18:36:31 by tkitahar          #+#    #+#             */
/*   Updated: 2024/12/13 12:50:55 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int signum)
{
	g_sig = signum;
}

void	ignore_sig(int signum)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_IGN;
	if (sigaction(signum, &sa, NULL) < 0)
		fatal_error("sigaction");
}

void	setup_sigint(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handler;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		fatal_error("sigaction");
}

int	check_state(void)
{
	if (g_sig == 0)
		return (0);
	else if (g_sig == SIGINT)
	{
		g_sig = 0;
		gs_readline_interrupted(SET, TRUE);
		gs_last_status(SET, ERROR_SIGINT);
		rl_replace_line("", 1);
		rl_done = 1;
		return (0);
	}
	return (0);
}

void	setup_signal(void)
{
	extern int	_rl_echo_control_chars;

	_rl_echo_control_chars = 1;
	rl_outstream = stderr;
	if (isatty(STDIN_FILENO))
		rl_event_hook = check_state;
	ignore_sig(SIGQUIT);
	setup_sigint();
}
