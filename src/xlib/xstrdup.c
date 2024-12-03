/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xstrdup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkitahar <tkitahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:12:49 by tkitahar          #+#    #+#             */
/*   Updated: 2024/12/03 14:14:51 by tkitahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*xstrdup(const char *str)
{
	char	*ret;

	ret = ft_strdup(str);
	if (ret == NULL)
		fatal_error("xstrdup");
	return (ret);
}
