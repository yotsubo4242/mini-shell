/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blank.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:54:05 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/10/21 19:09:00 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

t_bool	consume_blank(char **rest, char *line)
{
	if (is_blank(*line))
	{
		while (*line && is_blank(*line))
			line++;
		*rest = line;
		return (TRUE);
	}
	*rest = line;
	return (FALSE);
}
