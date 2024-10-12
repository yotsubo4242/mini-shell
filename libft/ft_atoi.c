/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:52:04 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/04/15 23:52:04 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	long long	res;
	int			flag;
	size_t		i;

	i = 0;
	while (ft_isspace(nptr[i]))
		i++;
	flag = 1;
	if (nptr[i] == '+' || nptr[i] == '-')
		if (nptr[i++] == '-')
			flag *= -1;
	res = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (res * flag > LONG_MAX / 10 \
		|| (res * flag == LONG_MAX / 10 && nptr[i] - '0' > LONG_MAX % 10))
			return ((int)LONG_MAX);
		if (res * flag < LONG_MIN / 10 \
		|| (res * flag == LONG_MIN / 10 && -(nptr[i] - '0') < LONG_MIN % 10))
			return ((int)LONG_MIN);
		res *= 10;
		res += nptr[i++] - '0';
	}
	return ((int)(res * flag));
}

// int	main(void)
// {
// 	char num[] = "-";

// 	printf("num: %s\n", num);
// 	printf("ft_atoi: %d\n", ft_atoi(num));
// 	printf("   atoi: %d\n", atoi(num));
// 	return (0);
// }
