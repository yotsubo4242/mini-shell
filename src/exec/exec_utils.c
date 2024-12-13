/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkitahar <tkitahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:35:10 by tkitahar          #+#    #+#             */
/*   Updated: 2024/12/13 15:37:42 by tkitahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_param_num(t_token *tok)
{
	size_t	param_num;

	param_num = 0;
	while (tok)
	{
		tok = tok->next;
		param_num++;
	}
	return (param_num);
}

void	validate_access(const char *path, const char *filename)
{
	if (path == NULL)
		err_exit(filename, "command not found", 127);
	if (*path == '\0')
		err_exit("''", "command not found", 127);
	if (access(path, F_OK) < 0)
	{
		if (!ft_strcmp(path, filename))
			err_exit(filename, "No such file or directory", 127);
		else
			err_exit(filename, "command not found", 127);
	}
	if (access(path, X_OK) < 0)
		err_exit(filename, "Permission denied", 126);
}

static size_t	expanded_token_len(t_token *tok)
{
	size_t	len;
	size_t	i;
	bool	is_word_head;

	len = 0;
	i = 0;
	is_word_head = true;
	while (tok->word[i] != '\0')
	{
		if (ft_isspace(tok->word[i]))
			is_word_head = true;
		else if (is_word_head)
		{
			is_word_head = false;
			len++;
		}
		i++;
	}
	return (len);
}

char	*dup_until_space(const char *s)
{
	size_t	len;
	size_t	i;
	char	*dup;

	len = 0;
	i = 0;
	while (s[i] != '\0' && !ft_isspace(s[i]))
	{
		len++;
		i++;
	}
	dup = xmalloc(len + 1);
	ft_strlcpy(dup, s, len + 1);
	return (dup);
}

size_t	argv_len(t_token *tok)
{
	size_t	len;

	len = 0;
	while (tok && !at_eof(tok))
	{
		if (tok->is_expanded)
			len += expanded_token_len(tok);
		else
			len++;
		tok = tok->next;
	}
	return (len);
}
