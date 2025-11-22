/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 02:45:57 by nkojima           #+#    #+#             */
/*   Updated: 2025/05/30 15:28:28 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

static const char	*skip_whitespace_and_sign(const char *str, int *sign)
{
	*sign = 1;
	while (ft_isspace((int)*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			*sign = -1;
		str++;
	}
	return (str);
}

static int	convert_digits(const char *str, int sign)
{
	long	result;
	long	limit;

	result = 0;
	limit = LONG_MAX / 10;
	while (ft_isdigit((int)*str))
	{
		if ((result > limit) || (result == limit && (*str - '0') > LONG_MAX
				% 10))
		{
			if (sign == 1)
				return ((int)LONG_MAX);
			else
				return ((int)LONG_MIN);
		}
		result = result * 10 + (*str - '0');
		str++;
	}
	return ((int)(sign * result));
}

/**
 * Converts a string to an integer.
 *
 * Skips leading whitespace, handles optional `+` or `-` sign, and converts
 * numeric characters to an integer until a non-digit is encountered.
 *
 * Params:
 * @str: The string to convert.
 *
 * Return:
 * The integer value represented by the string.
 */
int	ft_atoi(const char *str)
{
	int			sign;
	const char	*digits_start;

	digits_start = skip_whitespace_and_sign(str, &sign);
	return (convert_digits(digits_start, sign));
}

// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	char	str[42] = "9223372036854775807";

// 	printf("ft: %d\n", ft_atoi(str));
// 	printf("  : %d\n", atoi(str));
// 	return (0);
// }
