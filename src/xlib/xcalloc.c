/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xcalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkitahar <tkitahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:53:41 by tkitahar          #+#    #+#             */
/*   Updated: 2024/12/03 14:20:05 by tkitahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*xcalloc(size_t count, size_t size)
{
	void	*tmp;

	tmp = ft_calloc(count, size);
	if (tmp == NULL)
		fatal_error("xcalloc");
	return (tmp);
}
