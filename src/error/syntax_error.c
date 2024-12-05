/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkitahar <tkitahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:59:56 by tkitahar          #+#    #+#             */
/*   Updated: 2024/12/03 15:59:57 by tkitahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize_error(const char *location, char **rest, char *line)
{
	g_syntax_error = TRUE;
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "syntax error near unexpected character `%c' in %s\n", *line, location);
	while (*line)
		line++;
	*rest = line;
}

void	parse_error(const char *location, t_token **rest, t_token *tok)
{
	g_syntax_error = TRUE;
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "syntax error near unexpected token `%s' in %s\n",tok->word , location);
	while (tok->kind != TK_EOF)
		tok = tok->next;
	*rest = tok;
}
