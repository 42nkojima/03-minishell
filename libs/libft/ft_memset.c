/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:02:33 by nkojima           #+#    #+#             */
/*   Updated: 2025/05/30 18:35:08 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Fills the first `n` bytes of the memory area `buf` with the byte `ch`.
 *
 * Params:
 * @buf: Pointer to the memory area.
 * @ch: Byte value to fill.
 * @n: Number of bytes to fill.
 *
 * Return:
 * A pointer to the memory area `buf`.
 */
void	*ft_memset(void *buf, int ch, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)buf;
	while (n--)
		*ptr++ = (unsigned char)ch;
	return (buf);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	buf1[10];
// 	char	buf2[10];

// 	ft_memset(buf1, 'A', sizeof(buf1));
// 	memset(buf2, 'A', sizeof(buf2));
// 	printf("ft: %.*s\n", (int)sizeof(buf1), buf1);
// 	printf("  : %.*s\n", (int)sizeof(buf2), buf2);
// 	return (0);
// }
