/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:52:45 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/04/15 23:52:45 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
		str[i++] = (unsigned char)c;
	return (s);
}

// int	main(void)
// {
// 	char s1[] = "";
// 	char s2[] = "";
// 	char c = 'a';
// 	int n = 5;

// 	printf("ft_memset: %s\n", (unsigned char *)ft_memset(s1, c, n));
// 	printf("   memset: %s\n", (unsigned char *)memset(s2, c, n));
// 	return (0);
// }