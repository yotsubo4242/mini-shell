/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:53:07 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/04/15 23:53:07 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_all(char **strs, size_t size)
{
	if (!strs)
		return (NULL);
	while (size)
		free(strs[--size]);
	free(strs);
	return (NULL);
}

static int	count_strs(const char *s, char c)
{
	size_t	i;
	int		flag;
	int		res;

	i = 0;
	flag = 1;
	res = 0;
	while (s[i])
	{
		if (s[i] == c)
			flag = 1;
		else
		{
			if (flag)
				res++;
			flag = 0;
		}
		i++;
	}
	return (res);
}

static char	*ft_strcdup(const char *s, char c)
{
	char	*res;
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);
	len = 0;
	while (s[len] && s[len] != c)
		len++;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static size_t	search_next_c(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		size;
	int		n;
	size_t	i;

	if (!s)
		return (NULL);
	size = count_strs(s, c);
	res = (char **)malloc(sizeof(char *) * (size + 1));
	if (!res)
		return (NULL);
	n = 0;
	i = 0;
	while (s[i] && n < size)
	{
		while (s[i] == c)
			i++;
		res[n] = ft_strcdup(&s[i], c);
		if (!res[n])
			return (free_all(res, n));
		i += search_next_c(&s[i], c);
		n++;
	}
	res[n] = NULL;
	return (res);
}

// int	main(void)
// {
// 	char s[] = "xxx123456789xxx1234567890xxxxx";
// 	char c = 'x';
// 	char **res;
// 	int	i;

// 	printf("s: %s\n", s);
// 	printf("c: %c\n\n", c);
// 	res = ft_split(s, c);
// 	if (!res)
// 		return (0);
// 	i = 0;
// 	while (res[i])
// 	{
// 		printf("res[%d]: %s\n", i, res[i]);
// 		i++;
// 	}
// 	free_all(res, i);
// 	return (0);
// }
