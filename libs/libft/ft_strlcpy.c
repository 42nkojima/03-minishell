/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 19:31:38 by nkojima           #+#    #+#             */
/*   Updated: 2025/05/30 19:33:11 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Copies up to dstsize - 1 characters from the string `src` to `dst`,
 * null-terminating the result if dstsize is not 0.
 *
 * Params:
 * @dst: The destination buffer where the string will be copied.
 * @src: The source string to copy from.
 * @dstsize: The size of the destination buffer.
 *
 * Return:
 * The total length of the string it tried to create (length of src).
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	i = 0;
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

// #include <bsd/string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	ft_dst[10];
// 	size_t	ft_len;
// 	char	dst[10];
// 	size_t	len;

// 	ft_len = ft_strlcpy(ft_dst, "Hello, world!", sizeof(ft_dst));
// 	len = strlcpy(dst, "Hello, world!", sizeof(dst));
// 	printf("ft: %s %zu\n", ft_dst, ft_len);
// 	printf("  : %s %zu\n", dst, len);
// 	return (0);
// }
