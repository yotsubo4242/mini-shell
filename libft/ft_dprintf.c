/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:20:28 by yotsubo           #+#    #+#             */
/*   Updated: 2024/11/09 15:39:36 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	dprintf_error(const char *str)
{
	ft_printf("error: %s\n", str);
	exit(EXIT_FAILURE);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	size_t	i;
	va_list	ap;
	int		res;

	if (dup2(fd, STDOUT_FILENO) < 0)
		dprintf_error("dup2");
	if (close(fd) < 0)
		dprintf_error("close");
	va_start(ap, format);
	res = 0;
	i = -1;
	while (format[++i] != '\0')
	{
		if (format[i] == '%')
			res += reading_args(format[++i], ap);
		else
		{
			write(STDOUT_FILENO, &format[i], sizeof(char));
			res++;
		}
	}
	if (dup2(STDOUT_FILENO, fd) < 0)
		dprintf_error("dup2");
	return (res);
}