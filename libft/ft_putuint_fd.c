/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuint_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:38:56 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/06/27 16:48:07 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digit(unsigned int un)
{
	int	res;

	if (!un)
		return (1);
	res = 0;
	while (un)
	{
		un /= 10;
		res++;
	}
	return (res);
}

static long long	ft_power(int n, int power)
{
	long long	res;

	res = 1;
	while (power--)
		res *= n;
	return (res);
}

void	ft_putuint_fd(unsigned int un, int fd)
{
	int		digit;
	char	out_c;

	digit = count_digit(un);
	while (digit--)
	{
		out_c = un / ft_power(10, digit) + '0';
		write(fd, &out_c, sizeof(char));
		un %= ft_power(10, digit);
	}
}
