/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkitahar <tkitahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:28:48 by tkitahar          #+#    #+#             */
/*   Updated: 2024/12/10 16:50:42 by tkitahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_overflow(unsigned long val, unsigned long next, int is_neg)
{
	if (!is_neg)
	{
		if (val > (unsigned long)LONG_MAX / 10)
			return (1);
		if (val == (unsigned long)LONG_MAX / 10
			&& next > (unsigned long)LONG_MAX % 10)
			return (1);
	}
	if (val > ((unsigned long)LONG_MAX + 1) / 10)
		return (1);
	if (val == ((unsigned long)LONG_MAX + 1) / 10
		&& next > ((unsigned long)LONG_MAX + 1) % 10)
		return (1);
	return (0);
}

static long	culclate_strtol(const char *str, unsigned long val, int is_neg)
{
	while (ft_isdigit(*str))
	{
		if (is_overflow(val, *str - '0', is_neg))
		{
			errno = ERANGE;
			if (is_neg)
				return (LONG_MIN);
			return (LONG_MAX);
		}
		val = val * 10 + (*str - '0');
		str++;
	}
	return (val);
}

long	ft_strtol(const char *str)
{
	unsigned long	val;
	int				is_neg;
	long			ret;

	while (ft_isspace(*str))
		str++;
	is_neg = 0;
	if (is_plusminus(*str))
	{
		if (*str == '-')
			is_neg = 1;
		str++;
	}
	val = 0;
	ret = (long)culclate_strtol(str, val, is_neg);
	if (is_neg)
		ret = -ret;
	return (ret);
}
