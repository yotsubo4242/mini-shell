/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:53:34 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/04/15 23:53:34 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*res;

	if (!s)
		return (NULL);
	if (!len)
		return (ft_strdup(""));
	s_len = ft_strlen(s);
	if (start >= s_len)
		len = 0;
	else if (len > s_len - start)
		len = s_len - start;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

// int	main(void)
// {
// 	char s[] = "42";
// 	unsigned int	start =  0;
// 	size_t	len = 0;
// 	char	*res;

// 	res = ft_substr(s, start, len);
// 	printf("s: %s\nstart: %d\nlen: %ld\n\n", s, start, len);
// 	printf("ft_substr: %s\n", res);
// 	free(res);
// 	return (0);
// }