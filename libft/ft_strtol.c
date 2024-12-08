/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkitahar <tkitahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 16:24:53 by tkitahar          #+#    #+#             */
/*   Updated: 2024/12/08 16:25:11 by tkitahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <limits.h>

static int    is_overflow(unsigned long val, unsigned long next, int is_neg)
{
    if (is_neg)
    {
        if (val > ((unsigned long)LONG_MAX + 1) / 10)
            return (1);
        if (val == ((unsigned long)LONG_MAX + 1) / 10
            && next > ((unsigned long)LONG_MAX + 1) % 10)
            return (1);
    }
    else
    {
        if (val > (unsigned long)LONG_MAX / 10)
            return (1);
        if (val == (unsigned long)LONG_MAX / 10
            && next > (unsigned long)LONG_MAX % 10)
            return (1);
    }
    return (0);
}

long    ft_strtol(const char *str)
{
    unsigned long    val;
    int             is_neg;
    long            ret;

    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;
    is_neg = 0;
    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
            is_neg = 1;
        str++;
    }
    val = 0;
    while (*str >= '0' && *str <= '9')
    {
        if (is_overflow(val, *str - '0', is_neg))
        {
            errno = ERANGE;
            if (is_neg)
                return (LONG_MIN);
            return (LONG_MAX);
        }
        val = val * 10 + (*str - '0');
        str++;
    }
    ret = (long)val;
    if (is_neg)
        ret = -ret;
    return (ret);
}
