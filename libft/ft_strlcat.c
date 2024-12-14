/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 21:30:30 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/04/18 10:53:35 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	res;
	size_t	i;

	src_len = ft_strlen(src);
	if (!dstsize)
		return (src_len);
	dst_len = ft_strlen(dst);
	if (dst_len > dstsize)
		return (dstsize + src_len);
	else
		res = dst_len + src_len;
	while (*dst)
		dst++;
	dstsize -= dst_len;
	i = 0;
	while (src[i] && i + 1 < dstsize)
		*(dst++) = src[i++];
	*dst = '\0';
	return (res);
}

// int	main(void)
// {
// 	char *src = "12345";
// 	char dst1[64] = "1234567890";
// 	char dst2[64] = "1234567890";
// 	size_t	dstsize = 2;
// 	size_t	res1 = ft_strlcat(dst1, src, dstsize);
// 	size_t	res2 = strlcat(dst2, src, dstsize);

// 	printf("    src: %s\n", src);
// 	printf("dstsize: %zu\n", dstsize);
// 	printf(" ft dst: %s\n", dst1);
// 	printf(" ft res: %zu\n", res1);
// 	printf("ori dst: %s\n", dst2);
// 	printf("ori res: %zu\n", res2);
// 	return (0);
// }