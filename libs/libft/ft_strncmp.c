/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 23:34:32 by nkojima           #+#    #+#             */
/*   Updated: 2025/05/30 19:46:33 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * It compares only the first (at most) n bytes of s1 and s2.
 *
 * Params:
 * @s1: The first string to compare.
 * @s2: The second string to compare.
 * @n: The maximum number of characters to compare.
 *
 * Return:
 * - 0, if the `s1` and `s2` are equal.
 * - A negative value if `s1` is less than `s2`.
 * - A positive value if `s1` is greater than `s2`.
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	count;

	count = 0;
	while (count < n && *s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
		count++;
	}
	if (count == n)
		return (0);
	return ((const unsigned char)*s1 - (const unsigned char)*s2);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	size_t	n;
// 	char	s1[42] = "Hello, world!";
// 	char	s2[42] = "Helwo, w0rld!";

// 	n = 3;
// 	printf("ft: %d\n", ft_strncmp(s1, s2, n));
// 	printf("  : %d\n", strncmp(s1, s2, n));
// 	return (0);
// }
