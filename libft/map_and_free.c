/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_and_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:34:24 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/06/14 09:40:48 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*map_and_free(void	*res, void *for_free)
{
	if (for_free)
		free(for_free);
	return (res);
}
