/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 19:10:05 by nkojima           #+#    #+#             */
/*   Updated: 2025/05/30 20:16:45 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"

static int	ft_islower(int c)
{
	return ('a' <= c && c <= 'z');
}

/**
 * Converts a lowercase letter to uppercase.
 */
int	ft_toupper(int c)
{
	if (ft_islower(c))
		return (c + ('A' - 'a'));
	return (c);
}

// #include <ctype.h>
// #include <stdio.h>

// int	main(void)
// {
// 	printf("ft_('a'): %d\n", ft_toupper('a'));
// 	printf("toupper('a'): %d\n", toupper('a'));
// 	printf("ft_('A'): %d\n", ft_toupper('A'));
// 	printf("toupper('A'): %d\n", toupper('A'));
// 	return (0);
// }
