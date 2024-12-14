/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:20:28 by yotsubo           #+#    #+#             */
/*   Updated: 2024/12/12 16:54:06 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	dprintf_error(const char *str)
{
	ft_printf("error: %s\n", str);
	exit(EXIT_FAILURE);
}

static void	my_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) < 0)
		dprintf_error("dup2");
}

int	ft_dprintf(int fd, const char *format, ...)
{
	size_t		i;
	va_list		ap;
	int			res;
	int			saved_stdout;

	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout < 0)
		dprintf_error("dup");
	my_dup2(fd, STDOUT_FILENO);
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
	my_dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	return (res);
}
