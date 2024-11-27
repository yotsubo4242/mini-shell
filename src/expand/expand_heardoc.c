/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heardoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkitahar <tkitahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:03:29 by tkitahar          #+#    #+#             */
/*   Updated: 2024/11/13 16:10:30 by tkitahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_heardoc_line(char *line)
{
	char	*new_word;
	char 	*p;

	p = line;
	new_word = ft_calloc(1, sizeof(char));
	if (new_word == NULL)
		fatal_error("calloc");
	while (*p)
	{
		if (is_variable(p))
			expand_variable_str(&new_word, &p, p);
		else if (is_special_parameter(p))
			expand_special_parameter_str(&new_word, &p, p);
		else
			append_char(&new_word, *p++);
	}
	free(line);
	return (new_word);
}
