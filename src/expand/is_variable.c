/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_variable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkitahar <tkitahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:34:25 by tkitahar          #+#    #+#             */
/*   Updated: 2024/11/12 17:13:20 by tkitahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_alpha_under(char c)
{
	return (ft_isalpha(c) || c == '_');
}

t_bool	is_alpha_num_under(char c)
{
	return (is_alpha_under(c) || ft_isdigit(c));
}

t_bool	is_variable(char *s)
{
	return (s[0] == '$' && is_alpha_num_under(s[1]));
}
