/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:53:29 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/04/15 23:53:29 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*res;

	res = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			res = (char *)&s[i];
		i++;
	}
	if (!c)
		return ((char *)&s[i]);
	return (res);
}

// int	main(void)
// {
// 	char str[] = "12345674890";
// 	char c = 'a';

// 	printf("str: %s\n  c: %c\n\n", str, c);
// 	printf("ft_strrchr: %s\n", ft_strrchr(str, c));
// 	printf("   strrchr: %s\n", strrchr(str, c));
// 	return (0);
// }