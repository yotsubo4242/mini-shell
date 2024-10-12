/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:51:23 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/06/05 07:50:46 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst)
		return ;
	if (*lst)
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

// int	main(void)
// {
// 	char s1[] = "this is 1";
// 	char s2[] = "this is 2";
// 	char s3[] = "this is 3";
// 	t_list	*head;

// 	head = ft_lstnew(s1);
// 	ft_lstadd_back(&head, ft_lstnew(s2));
// 	ft_lstadd_back(&head, ft_lstnew(s3));
// 	while (head)
// 	{
// 		printf("%s\n", (char *)head->content);
// 		head = head->next;
// 	}
// 	return (0);
// }