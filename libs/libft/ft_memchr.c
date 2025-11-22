/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 01:14:26 by nkojima           #+#    #+#             */
/*   Updated: 2025/05/30 18:06:43 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Searches for the first occurrence of the byte `c` in the first `n` bytes
 * of the memory area `s`.
 *
 * Params:
 * @s: Memory area to search.
 * @c: Byte to find (converted to unsigned char).
 * @n: Number of bytes to search.
 *
 * Return:
 * Pointer to the first occurrence of `c`, or NULL if not found.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*target;
	unsigned char		search;
	size_t				count;

	count = 0;
	search = (unsigned char)c;
	target = (const unsigned char *)s;
	while (count < n)
	{
		if (*target == search)
			return ((void *)target);
		target++;
		count++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char			target[] = {0x00, 0x20, 0x30, 0x20, 0x40};
// 	unsigned char	search;
// 	void			*ft_ptr;
// 	void			*ptr;

// 	search = 0x40;
// 	// libft
// 	ft_ptr = ft_memchr(target, search, sizeof(target));
// 	if (ft_ptr)
// 		printf("ft: found at index %ld\n", (unsigned char *)ft_ptr
// 			- (unsigned char *)target);
// 	else
// 		printf("ft: not found");
// 	// 標準
// 	ptr = memchr(target, search, sizeof(target));
// 	if (ptr)
// 		printf("  : found at index %ld\n", (unsigned char *)ptr
// 			- (unsigned char *)target);
// 	else
// 		printf("  : not found");
// 	return (0);
// }
