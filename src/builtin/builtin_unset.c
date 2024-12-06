/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:20:12 by yotsubo           #+#    #+#             */
/*   Updated: 2024/11/21 14:38:11 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char **argv)
{
	int		status;
	size_t	i;

	status = 0;
	i = 1;
	while (argv[i])
	{
		map_unset(g_env, argv[i]);
		status = 0;
		i++;
	}
	return (status);
}
