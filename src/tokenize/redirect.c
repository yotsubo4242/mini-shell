/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:24:51 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/10/21 19:14:26 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_redirect(char *line)
{
	static char *const redirects[] = {"<", ">", "<<", ">>"};
	size_t	i;

	i = 0;
	while (i < sizeof(redirects) / sizeof(*redirects))
	{
		if (startswith(line, redirects[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	s_is_tar(char *s, char *tar)
{
	if (ft_strncmp(s, tar, ft_strlen(tar)))
		return (FALSE);
	s += ft_strlen(tar);
	if (is_blank(*s) || *s == '\0')
		return (TRUE);
	return (FALSE);
}

static t_token	*red_in(char **rest, char *line)
{
	char				*red;

	if (s_is_tar(line, "<"))
	{
		red = ft_strdup("<");
		if (!red)
			fatal_error("strdup");
		*rest = line + ft_strlen(red);
		return (new_token(red, TK_IRED));
	}
	return (NULL);
}

static t_token	*red_out(char **rest, char *line)
{
	char				*red;

	if (s_is_tar(line, ">"))
	{
		red = ft_strdup(">");
		if (!red)
			fatal_error("strdup");
		*rest = line + ft_strlen(red);
		return (new_token(red, TK_ORED));
	}
	return (NULL);
}

static t_token	*red_heredoc(char **rest, char *line)
{
	char	*red;

	if (s_is_tar(line, "<<"))
	{
		red = ft_strdup("<<");
		if (!red)
			fatal_error("strdup");
		*rest = line + ft_strlen(red);
		return (new_token(red, TK_HEREDOC));
	}
	return (NULL);
}

static t_token	*red_append(char **rest, char *line)
{
	char	*red;

	if (s_is_tar(line, ">>"))
	{
		red = ft_strdup(">>");
		if (!red)
			fatal_error("strdup");
		*rest = line + ft_strlen(red);
		return (new_token(red, TK_APPEND));
	}
	return (NULL);
}

t_token	*redirect(char **rest, char *line)
{
	t_token	*tok;

	tok = red_heredoc(rest, line);
	if (tok)
		return (tok);
	tok = red_in(rest, line);
	if (tok)
		return (tok);
	tok = red_append(rest, line);
	if (tok)
		return (tok);
	tok = red_out(rest, line);
	if (tok)
		return (tok);
	return (new_token(NULL, TK_EOF));
}
