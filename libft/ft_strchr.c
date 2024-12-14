/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:53:09 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/04/15 23:53:09 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (!c)
		return ((char *)&s[i]);
	return (NULL);
}

// int	main(void)
// {
// 	char str[] = "12345674890";
// 	char c = '4';

// 	printf("str: %s\n  c: %c\n\n", str, c);
// 	printf("ft_strchr: %s\n", ft_strchr(str, c));
// 	printf("   strchr: %s\n", strchr(str, c));
// 	return (0);
// }