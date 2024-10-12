/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:52:21 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/04/15 23:52:21 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') \
			|| (c >= '0' && c <= '9'));
}

// int	main(void)
// {
// 	char c = 'a';
// 	printf("ft_isalnum: %d\n", ft_isalnum(c));
// 	printf("isalnum: %d\n", isalnum(c));
// 	return (0);
// }