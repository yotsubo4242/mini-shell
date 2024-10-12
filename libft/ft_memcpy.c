/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:52:40 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/04/15 23:52:40 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dstp;
	unsigned char	*srcp;

	dstp = (unsigned char *)dst;
	srcp = (unsigned char *)src;
	if (!dstp && !srcp)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dstp[i] = srcp[i];
		i++;
	}
	return (dst);
}

// int main(void)
// {
// 	char s1[] = "1234567890";
// 	char s2[] = "1234567890";
// 	char d1[] = "asdfghjkl";
// 	char d2[] = "asdfghjkl";
// 	size_t	len = 1;

// 	printf("ft_memcpy: %s\n", (unsigned char *)ft_memcpy(s1, d1, len));
// 	printf("   memcpy: %s\n", (unsigned char *)memcpy(s2, d2, len));
// 	return (0);
// }