/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:51:31 by nkojima           #+#    #+#             */
/*   Updated: 2025/05/30 15:33:40 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_islower(int c)
{
	return ('a' <= c && c <= 'z');
}

static int	ft_isupper(int c)
{
	return ('A' <= c && c <= 'Z');
}

/**
 * Checks if a character is an alphabetic letter (a-z or A-Z).
 *
 * Params:
 * @c: The character to check.
 *
 * Return:
 * - 1 if the character is alphabetic.
 * - 0 otherwise.
 */
int	ft_isalpha(int c)
{
	return (ft_islower(c) || ft_isupper(c));
}

// #include <ctype.h>
// #include <stdio.h>

// int	main(void)
// {
// 	printf("ft_isalpha('a'): %d\n", ft_isalpha('a'));
// 	printf("isalpha('a'): %d\n", isalpha('a'));
// 	printf("ft_isalpha(EOF): %d\n", ft_isalpha(EOF));
// 	printf("isalpha(EOF): %d\n", isalpha(EOF));
// 	printf("ft_isalpha(0x0f): %d\n", ft_isalpha(0x0f));
// 	printf("isalpha(0x0f): %d\n", isalpha(0x0f));
// 	return (0);
// }
