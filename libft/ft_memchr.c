/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:52:35 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/04/15 23:52:35 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *b, int c, size_t len)
{
	unsigned char	*bp;
	size_t			i;

	bp = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		if (bp[i] == (unsigned char)c)
			return (&bp[i]);
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char s[] = "12345678901234567890";
// 	char c = 'b';
// 	int	len = 100;

// 	printf("  s: %s\n  c: %c\nlen: %d\n", s, c, len);
// 	printf("ft_memchr: %s\n", (char *)ft_memchr(s, c, len));
// 	printf("   memchr: %s\n", (char *)memchr(s, c, len));
// }