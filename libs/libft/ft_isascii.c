/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:51:28 by nkojima           #+#    #+#             */
/*   Updated: 2025/05/30 18:02:04 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Checks if a character is an ASCII character (0 to 127).
 *
 * Params:
 * @c: The character to check.
 *
 * Return:
 * - 1 if the character is ASCII.
 * - 0 otherwise.
 */
int	ft_isascii(int c)
{
	return (0 <= c && c <= 127);
}

// #include <ctype.h>
// #include <stdio.h>

// int	main(void)
// {
// 	printf("ft_isascii('!'): %d\n", ft_isascii('!'));
// 	printf("isascii('!'): %d\n", isascii('!'));
// 	printf("ft_isascii(EOF): %d\n", ft_isascii(EOF));
// 	printf("isascii(EOF): %d\n", isascii(EOF));
// 	return (0);
// }
