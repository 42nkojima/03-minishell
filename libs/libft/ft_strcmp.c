/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 23:00:04 by nkojima           #+#    #+#             */
/*   Updated: 2025/10/17 11:55:25 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Compares two strings lexicographically.
 *
 * This function compares the strings s1 and s2 character by character
 * until it finds a difference or reaches the end of either string.
 * The comparison is based on the ASCII values of the characters.
 *
 * Params:
 * @s1: The first string to compare.
 * @s2: The second string to compare.
 *
 * Return:
 * - 0, if s1 and s2 are equal.
 * - A negative value if s1 is less than s2.
 * - A positive value if s1 is greater than s2.
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	count;

	count = 0;
	while (s1[count] && s1[count] == s2[count])
		count++;
	return ((unsigned char)s1[count] - (unsigned char)s2[count]);
}
