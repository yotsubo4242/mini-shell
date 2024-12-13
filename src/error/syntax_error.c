/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:59:56 by tkitahar          #+#    #+#             */
/*   Updated: 2024/12/13 16:36:28 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize_error(const char *location, char **rest, char *line)
{
	gs_syntax_error(SET, TRUE);
	perror_prefix();
	ft_dprintf(STDERR_FILENO, \
		"syntax error near unexpected character `%c' in %s\n", *line, location);
	while (*line)
		line++;
	*rest = line;
}

void	parse_error(const char *location, t_token **rest, t_token *tok)
{
	gs_syntax_error(SET, TRUE);
	perror_prefix();
	ft_dprintf(STDERR_FILENO, \
		"syntax error near unexpected token `%s' in %s\n", tok->word, location);
	while (tok->kind != TK_EOF)
		tok = tok->next;
	*rest = tok;
}
