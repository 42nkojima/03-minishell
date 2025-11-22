/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 19:31:35 by nkojima           #+#    #+#             */
/*   Updated: 2025/05/30 19:31:04 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Appends `src` to the end of `dst`, ensuring null-termination.
 *
 * Params:
 * @dst: The destination buffer.
 * @src: The source string to append.
 * @dstsize: The total size of the destination buffer.
 *
 * Return:
 * The total length of the string it tried to create (dst + src).
 * If the return value is >= dstsize, the output was truncated.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	dst_len = ft_strlen(dst);
	if (dst_len >= dstsize)
		return (dstsize + src_len);
	i = 0;
	while (src[i] && (dst_len + i) < (dstsize - 1))
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	if ((dst_len + i) < dstsize)
		dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
// -lbsd
// #include <bsd/string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	ft_dst[20] = "Hello, ";
// 	char	ft_src[] = "world!";
// 	size_t	ft_result;
// 	char	dst[20] = "Hello, ";
// 	char	src[] = "world!";
// 	size_t	result;

// 	ft_result = ft_strlcat(NULL, ft_src, 0);
// 	printf("ft: dst = \"%s\", size = %zu\n", (char *)NULL, ft_result);
// 	result = strlcat(NULL, src, 0);
// 	printf("  : dst = \"%s\", size = %zu\n", (char *)NULL, result);
// 	return (0);
// }
