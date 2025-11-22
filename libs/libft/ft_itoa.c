/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:13:17 by nkojima           #+#    #+#             */
/*   Updated: 2025/05/30 18:05:11 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Counts the number of digits in an integer */
static size_t	count_digits(long n)
{
	size_t	count;

	count = 0;
	if (n <= 0)
		count = 1;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

/**
 * Converts an integer to a string
 *
 * Params:
 * @n: The integer to convert
 *
 * Return:
 * A new allocated string representing the integer,
 * or NULL if allocation fails
 */
char	*ft_itoa(int n)
{
	char	*str;
	size_t	digits;
	long	num;

	num = n;
	digits = count_digits(num);
	str = malloc(sizeof(*str) * (digits + 1));
	if (!str)
		return (NULL);
	str[digits] = '\0';
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	if (num == 0)
		str[0] = '0';
	while (num > 0)
	{
		str[--digits] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*result;
// 	int		test_values[] = {0, 42, -42, 2147483647, -2147483648, 123456789,
// 				-123456789, 1, -1};
// 	int		i;
// 	int		num_tests;

// 	num_tests = sizeof(test_values) / sizeof(test_values[0]);
// 	i = 0;
// 	while (i < num_tests)
// 	{
// 		result = ft_itoa(test_values[i]);
// 		printf("Input: %d\nOutput: \"%s\"\n\n", test_values[i], result);
// 		free(result);
// 		i++;
// 	}
// 	return (0);
// }
