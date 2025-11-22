/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 19:27:15 by nkojima           #+#    #+#             */
/*   Updated: 2025/05/30 18:34:05 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Copies n bytes from memory area src to memory area dst.
 *
 * Params:
 * @dst: The destination memory area.
 * @src: The source memory area.
 * @cpy_size: The number of bytes to copy.
 *
 * Return:
 * A pointer to the destination memory area (dst).
 */
void	*ft_memcpy(void *dst, const void *src, size_t cpy_size)
{
	unsigned char		*dst_ptr;
	const unsigned char	*src_ptr;

	if (cpy_size == 0 || dst == src)
		return (dst);
	dst_ptr = (unsigned char *)dst;
	src_ptr = (const unsigned char *)src;
	while (cpy_size--)
		*dst_ptr++ = *src_ptr++;
	return (dst);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	ft_src[20] = "Hello, world!";
// 	char	ft_dst[20] = {0};
// 	char	src[20] = "Hello, world!";
// 	char	dst[20] = {0};

// 	ft_memcpy(ft_dst, ft_src, 13);
// 	printf("ft: dst = \"%s\"\n", ft_dst);
// 	memcpy(dst, src, 13);
// 	printf("  : dst = \"%s\"\n", dst);
// 	// memcpy(NULL, src, 5);
// 	// ft_memcpy(NULL, src, 5);
// 	return (0);
// }
