/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:24:51 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/10/16 21:17:14 by yuotsubo         ###   ########.fr       */
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

t_token	*redirect(char **rest, char *line)
{
	static char	*const	redirects[] = {"<", ">", "<<", ">>"};
	size_t				i;
	char				*red;

	i = 0;
	while (i < sizeof(redirects) / sizeof(*redirects))
	{
		if (startswith(line, redirects[i]))
		{
			red = ft_strdup(redirects[i]);
			if (!red)
				fatal_error("strdup");
			*rest = line + ft_strlen(red);
			return (new_token(red, TK_RED));
		}
	}
	return (new_token(NULL, TK_EOF));
}
