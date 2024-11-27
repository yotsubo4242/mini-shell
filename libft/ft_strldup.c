/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strldup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkitahar <tkitahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:54:05 by tkitahar          #+#    #+#             */
/*   Updated: 2024/11/27 14:54:13 by tkitahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strldup(const char *s, int len)
{
	char	*str;

	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	if (!(ft_memcpy(str, s, len)))
		return (NULL);
	*(str + len) = 0;
	return (str);
}

// #include <limits.h>
// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	*a1;
// 	char	*a2;

// 	a1 = "12345";
// 	a2 = "12345";
// 	printf("\n");
// 	printf("ans\t %s \n", strdup(a1));
// 	printf("ans\t %s \n", ft_strdup(a2));
// 	printf("\n");
// 	return (0);
// }
