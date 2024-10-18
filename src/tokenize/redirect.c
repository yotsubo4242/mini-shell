/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:24:51 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/10/18 19:23:16 by yotsubo          ###   ########.fr       */
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

static t_token	*in_redirect(char **rest, char *line)
{
	static char *const	in_reds[] = {"<", "<<"};
	size_t				i;
	char				*red;

	i = 0;
	while (i < sizeof(in_reds) / sizeof(*in_reds))
	{
		if (startswith(line, in_reds[i]))
		{
			red = ft_strdup(in_reds[i]);
			if (!red)
				fatal_error("strdup");
			*rest = line + ft_strlen(red);
			return (new_token(red, TK_IRED));
		}
	}
	return (NULL);
}

static t_token	*out_redirect(char **rest, char *line)
{
	static char *const	out_reds[] = {">", ">>"};
	size_t				i;
	char				*red;

	i = 0;
	while (i < sizeof(out_reds) / sizeof(*out_reds))
	{
		if (startswith(line, out_reds[i]))
		{
			red = ft_strdup(out_reds[i]);
			if (!red)
				fatal_error("strdup");
			*rest = line + ft_strlen(red);
			return (new_token(red, TK_ORED));
		}
	}
	return (NULL);
}

t_token	*redirect(char **rest, char *line)
{
	t_token	*tok;

	tok = in_redirect(rest, line);
	if (tok)
		return (tok);
	tok = out_redirect(rest, line);
	if (tok)
		return (tok);
	return (new_token(NULL, TK_EOF));
}
