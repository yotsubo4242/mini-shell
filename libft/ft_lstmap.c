/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:33:34 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/04/18 22:01:16 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	*f(void *content)
// {
// 	static int	i = 1000;

// 	(void)content;
// 	return (ft_itoa(i++));
// }

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*res;
	t_list	*new;

	if (!lst)
		return (NULL);
	if (!f || !del)
		return (lst);
	tmp = lst;
	res = NULL;
	while (tmp)
	{
		new = ft_lstnew(f(tmp->content));
		if (!new && res)
		{
			ft_lstclear(&res, del);
			return (NULL);
		}
		if (!res)
			res = new;
		else
			ft_lstadd_back(&res, new);
		tmp = tmp->next;
	}
	return (res);
}

// int	main(void)
// {
// 	char *s1 = strdup("this is 1");
// 	char *s2 = strdup("this is 2");
// 	char *s3 = strdup("this is 3");
// 	t_list	*head;
// 	t_list	*tmp;

// 	head = ft_lstnew(s1);
// 	ft_lstadd_front(&head, ft_lstnew(s2));
// 	ft_lstadd_front(&head, ft_lstnew(s3));
// 	tmp = head;
// 	while (tmp)
// 	{
// 		printf("%s\n", (char *)tmp->content);
// 		tmp = tmp->next;
// 	}
// 	head = ft_lstmap(head, &f, &free);
// 	while (head)
// 	{
// 		printf("%s\n", (char *)head->content);
// 		head = head->next;
// 	}
// 	ft_lstclear(&head, &free);
// 	return (0);
// }