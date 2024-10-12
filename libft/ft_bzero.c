/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:52:11 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/04/15 23:52:11 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *b, size_t len)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)b;
	i = 0;
	while (i < len)
		str[i++] = 0;
}

// int	main(void)
// {
// 	char s1[] = "1234567890";
// 	char s2[] = "1234567890";
// 	int n = 5;

// 	ft_bzero(s1, n);
// 	bzero(s2, n);
// 	printf("---- ft_bzero ----\n");
// 	for (int i = 0; i < 10; i++)
// 		printf("%d: %d\n", i, s1[i]);
// 	printf("----    bzero ----\n");
// 	for (int i = 0; i < 10; i++)
// 		printf("%d: %d\n", i, s2[i]);
// 	return (0);
// }