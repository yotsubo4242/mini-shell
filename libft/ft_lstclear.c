/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:14:06 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/04/18 22:02:14 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = next;
	}
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
// 	while (head)
// 	{
// 		printf("%s\n", (char *)head->content);
// 		head = head->next;
// 	}
// 	return (0);
// }