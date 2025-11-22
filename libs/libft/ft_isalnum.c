/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:51:36 by nkojima           #+#    #+#             */
/*   Updated: 2025/05/30 15:31:49 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Checks if a character is alphanumeric (a letter or a digit).
 *
 * Params:
 * @c: The character to check.
 *
 * Return:
 * - 1 if the character is alphanumeric.
 * - 0 otherwise.
 */
int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

// #include <ctype.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int	c;

// 	c = EOF;
// 	printf("ft_isalnum(EOF): %d\n", ft_isalnum(c));
// 	printf("isalnum(EOF): %d\n", isalnum(c));
// 	printf("ft_isalnum('2'): %d\n", ft_isalnum('2'));
// 	printf("isalnum('2'): %d\n", isalnum('2'));
// 	printf("ft_isalnum('a'): %d\n", ft_isalnum('a'));
// 	printf("isalnum('a'): %d\n", isalnum('a'));
// 	printf("ft_isalnum('?'): %d\n", ft_isalnum('?'));
// 	printf("isalnum('?'): %d\n", isalnum('?'));
// 	return (0);
// }
