/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:58:09 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/04/20 19:58:09 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	reading_args(const char flag, va_list ap)
{
	int	len;

	if (flag == 'd' || flag == 'i')
		len = __printf_putint(va_arg(ap, int));
	else if (flag == 'u')
		len = __printf_putuint(va_arg(ap, unsigned int));
	else if (flag == 'x')
		len = __printf_puthex((t_ull)va_arg(ap, unsigned int), LOW);
	else if (flag == 'X')
		len = __printf_puthex((t_ull)va_arg(ap, unsigned int), UP);
	else if (flag == 'p')
		len = __printf_puthex((t_ull)va_arg(ap, void *), ADR);
	else if (flag == 's')
		len = __printf_putstr(va_arg(ap, char *));
	else if (flag == 'c')
		len = __printf_putchar(va_arg(ap, int));
	else if (flag == '%')
		len = __printf_putchar('%');
	else
		len = -1;
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	int		res;
	int		args_len;

	va_start(ap, format);
	i = -1;
	res = 0;
	while (format[++i])
	{
		if (format[i] == '%')
		{
			args_len = reading_args(format[++i], ap);
			if (args_len < 0)
				return (res);
			res += args_len;
		}
		else
		{
			write(STDOUT_FILENO, &format[i], sizeof(char));
			res++;
		}
	}
	return (res);
}

// int	main(void)
// {
// 	char	c = '\0';
// 	printf("res: %d\n", printf("123%c213", c));
// 	return (0);
// }