/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heardoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:03:29 by tkitahar          #+#    #+#             */
/*   Updated: 2024/12/13 16:47:34 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_heardoc_line(char *line)
{
	char	*new_word;
	char	*p;

	p = line;
	new_word = xcalloc(1, sizeof(char));
	while (*p)
	{
		if (is_variable(p))
			expand_variable_str(&new_word, &p, p, NULL);
		else if (is_special_parameter(p))
			expand_special_parameter_str(&new_word, &p, p);
		else
			append_char(&new_word, *p++);
	}
	free(line);
	return (new_word);
}
