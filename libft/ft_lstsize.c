/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:59:18 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/04/18 21:59:18 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	size;

	if (!lst)
		return (0);
	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

// int	main(void)
// {
// 	char s1[] = "this is 1";
// 	char s2[] = "this is 2";
// 	char s3[] = "this is 3";
// 	t_list	*head;

// 	head = ft_lstnew(s1);
// 	ft_lstadd_front(&head, ft_lstnew(s2));
// 	ft_lstadd_front(&head, ft_lstnew(s3));
// 	printf("size: %d\n", ft_lstsize(head));
// 	return (0);
// }