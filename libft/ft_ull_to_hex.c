/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ull_to_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:24:09 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/04/25 09:24:09 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_digits(t_ull ulln)
{
	size_t	digits;

	if (!ulln)
		return (1);
	digits = 0;
	while (ulln)
	{
		digits++;
		ulln /= 16;
	}
	return (digits);
}

static t_ull	ft_power(int n, int power)
{
	t_ull	res;

	res = 1;
	while (power--)
		res *= n;
	return (res);
}

static int	flag_check(int flag, char *res)
{
	if (flag == ADR)
	{
		res[0] = '0';
		res[1] = 'x';
		return (2);
	}
	else
		return (0);
}

char	*ft_ull_to_hex(t_ull ulln, int flag)
{
	size_t	len;
	size_t	i;
	char	*res;
	int		tmp;

	len = count_digits(ulln);
	res = (char *)malloc(sizeof(char) * (len + 3));
	if (!res)
		return (NULL);
	i = flag_check(flag, res);
	while (len--)
	{
		tmp = ulln / ft_power(16, len);
		if (tmp < 10)
			res[i++] = tmp + '0';
		else
			res[i++] = tmp - 10 + 'a';
		ulln %= ft_power(16, len);
	}
	res[i] = '\0';
	return (res);
}

// int	main(void)
// {
// 	char	*res;

// 	res = ft_ull_to_hex(0);
// 	printf("%s\n", res);
// 	free(res);
// 	return (0);
// }