/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 21:44:23 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/04/18 10:08:01 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	res;

	res = ft_strlen(src);
	if (!dstsize)
		return (res);
	i = 0;
	while (src[i] && --dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (res);
}

// int	main(void)
// {
// 	char *src = "1234567890";
// 	char dst1[10];
// 	char dst2[10];
// 	size_t	dstsize = 5;
// 	size_t	res1 = ft_strlcpy(dst1, src, dstsize);
// 	size_t	res2 = strlcpy(dst2, src, dstsize);

// 	printf("   src: %s\n", src);
// 	printf("ft dst: %s\n", dst1);
// 	printf("ft res: %zu\n", res1);
// 	printf("or dst: %s\n", dst2);
// 	printf("or res: %zu\n", res2);
// 	return (0);
// }