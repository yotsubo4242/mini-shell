/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 10:56:05 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/12/14 11:02:35 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_minishell(t_node *node)
{
	char	**envp;
	int		status;

	envp = get_environ(gs_env(GET, NULL));
	status = main(0, NULL, envp);
	free_argv(envp);
	return (status);
}
