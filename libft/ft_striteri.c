/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:41:12 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/04/17 18:41:12 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static void	test_func(unsigned int i, char *cp)
// {
// 	(void)i;
// 	*cp += 1;
// }

// char	*ft_strdup(const char *str)
// {
// 	size_t	i;
// 	size_t	len;
// 	char	*res;

// 	len = 0;
// 	while (str[len])
// 		len++;
// 	res = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!res)
// 		return (NULL);
// 	i = 0;
// 	while (str[i])
// 	{
// 		res[i] = str[i];
// 		i++;
// 	}
// 	res[i] = '\0';
// 	return (res);
// }

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f((unsigned int)i, &s[i]);
		i++;
	}
}

// int	main(void)
// {
// 	char ori[] = "";
// 	char *s = ft_strdup(ori);

// 	ft_striteri(s, &test_func);
// 	printf("ori: %s\n", ori);
// 	printf("  s: %s\n", s);
// 	free(s);
// 	return (0);
// }