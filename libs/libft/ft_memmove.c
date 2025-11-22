/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 19:25:26 by nkojima           #+#    #+#             */
/*   Updated: 2025/05/30 18:34:37 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Copies memory area, handling overlapping regions safely.
 *
 * Params:
 * @dst: The destination buffer where the memory will be copied to.
 * @src: The source buffer from which the memory will be copied.
 * @cpy_size: The number of bytes to copy.
 *
 * Return:
 * A pointer to the destination buffer `dst`.
 * */
void	*ft_memmove(void *dst, const void *src, size_t cpy_size)
{
	unsigned char		*dst_ptr;
	const unsigned char	*src_ptr;

	if (cpy_size == 0 || dst == src)
		return (dst);
	dst_ptr = (unsigned char *)dst;
	src_ptr = (const unsigned char *)src;
	if (dst_ptr < src_ptr)
	{
		while (cpy_size--)
			*dst_ptr++ = *src_ptr++;
	}
	else
	{
		dst_ptr += cpy_size;
		src_ptr += cpy_size;
		while (cpy_size--)
			*(--dst_ptr) = *(--src_ptr);
	}
	return (dst);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	ft_str[20] = "Hello, world!";
// 	char	str[20] = "Hello, world!";

// 	ft_memmove(ft_str, ft_str + 1, 13);
// 	printf("ft: = \"%s\"\n", ft_str + 1);
// 	ft_memmove(ft_str + 1, ft_str, 13);
// 	printf("ft: = \"%s\"\n", ft_str);
// 	memmove(str, str + 1, 13);
// 	printf("  : = \"%s\"\n", str + 1);
// 	memmove(str + 1, str, 13);
// 	printf("  : = \"%s\"\n", str);
// 	return (0);
// }
