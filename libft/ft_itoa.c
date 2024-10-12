/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:41:06 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/04/17 18:41:06 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_pow(int n, int power)
{
	int	res;

	res = 1;
	while (power--)
		res *= n;
	return (res);
}

static int	count_digit(long long lln)
{
	int	res;

	if (!lln)
		return (1);
	res = 0;
	if (lln < 0)
	{
		lln *= -1;
		res++;
	}
	while (lln)
	{
		lln /= 10;
		res++;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	char		*res;
	long long	lln;
	int			digit;
	int			i;

	lln = (long long)n;
	digit = count_digit(lln);
	res = (char *)malloc(sizeof(char) * (digit + 1));
	if (!res)
		return (NULL);
	i = 0;
	if (lln < 0)
	{
		lln *= -1;
		res[i++] = '-';
		digit--;
	}
	while (digit--)
	{
		res[i++] = lln / ft_pow(10, digit) + '0';
		lln %= ft_pow(10, digit);
	}
	res[i] = '\0';
	return (res);
}

// int	main(void)
// {
// 	int	n = 12;
// 	char *res;

// 	res = ft_itoa(n);
// 	printf("      n: %d\n", n);
// 	printf("ft_itoa: %s\n", res);
// 	free(res);
// 	return (0);
// }