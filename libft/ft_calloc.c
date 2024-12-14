/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:52:14 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/04/15 23:52:14 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*res;
	size_t			i;

	if (size > 0 && nmemb > (size_t)(-1) / size)
		return (NULL);
	if (!nmemb || !size)
	{
		nmemb = 1;
		size = 1;
	}
	res = (unsigned char *)malloc(nmemb * size);
	if (!res)
		return (NULL);
	i = 0;
	while (i < size * nmemb)
	{
		res[i] = 0;
		i++;
	}
	return ((void *)res);
}

// int	main(void)
// {
// 	// size_t	nmemb = sizeof(int);
// 	size_t	size = 4;
// 	int	*res;

// 	res = (int *)ft_calloc(INT_MIN, size);
// 	for (size_t i = 0; i < size; i++)
// 		printf("res[%ld]: %d\n", i, res[i]);
// 	free(res);
// 	return (0);
// }