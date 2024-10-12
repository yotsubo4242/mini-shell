/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:52:43 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/04/15 23:52:43 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const	void *src, size_t len)
{
	unsigned char	*dstp;
	unsigned char	*srcp;
	size_t			i;

	dstp = (unsigned char *)dst;
	srcp = (unsigned char *)src;
	if (!dstp && !srcp)
		return (NULL);
	if (dstp > srcp)
	{
		while (len--)
			dstp[len] = srcp[len];
	}
	else
	{
		i = 0;
		while (i < len)
		{
			dstp[i] = srcp[i];
			i++;
		}
	}
	return (dstp);
}

// int main(void)
// {
// 	char s1[] = "1234567890";
// 	char s2[] = "1234567890";
// 	char d1[] = "asdfghjkl";
// 	char d2[] = "asdfghjkl";
// 	size_t	len = 1;

// 	printf("ft_memmove: %s\n", (unsigned char *)ft_memmove(s1, d1, len));
// 	printf("   memmove: %s\n", (unsigned char *)memmove(s2, d2, len));
// 	return (0);
// }