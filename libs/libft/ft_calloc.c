/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:32:00 by nkojima           #+#    #+#             */
/*   Updated: 2025/05/30 15:31:10 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Allocates memory for an array and initializes it to zero.
 *
 * Params:
 * @nmemb: Number of elements.
 * @size: Size of each element in bytes.
 *
 * Return:
 * - Pointer to the allocated memory, or NULL on failure.
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total;
	void	*ptr;

	if (!nmemb || !size)
		return (malloc(0));
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	total = nmemb * size;
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total);
	return (ptr);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// int	main(void)
// {
// 	size_t	n;
// 	void	*p1;
// 	void	*p2;

// 	n = 5;
// 	p1 = calloc(n, 1);
// 	p2 = ft_calloc(n, 1);
// 	/* メモリ内容を比較。ゼロ初期化なら memcmp == 0 */
// 	printf("%s\n", memcmp(p1, p2, n) == 0 ? "same" : "different");
// 	free(p1);
// 	free(p2);
// 	return (0);
// }
