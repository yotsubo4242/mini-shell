/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:53:12 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/04/15 23:53:12 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	i;
	size_t	len;
	char	*res;

	len = 0;
	while (str[len])
		len++;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

// int	main(void)
// {
// 	char *str = NULL;
// 	char *res1;
// 	char *res2;

// 	res1 = ft_strdup(str);
// 	res2 = strdup(str);
// 	printf("      str: %s\n  address: %p\n\n", str, str);
// 	printf("ft_strdup: %s\n  address: %p\n\n", res1, res1);
// 	printf("   strdup: %s\n  address: %p\n", res2, res2);
// 	return (0);
// }