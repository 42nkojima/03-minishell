/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:32:20 by nkojima           #+#    #+#             */
/*   Updated: 2025/05/30 19:10:07 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Duplicates a string by allocating memory and copying its content.
 *
 * Params:
 * @str: The string to duplicate.
 *
 * Return:
 * - A pointer to the duplicated string, or NULL on failure.
 */
char	*ft_strdup(const char *str)
{
	size_t	str_len;
	char	*ptr;

	str_len = ft_strlen(str);
	ptr = malloc(str_len + 1);
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, str, str_len + 1);
	return (ptr);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	str[42] = "Hello, world!";
// 	char	*ft_dup;
// 	char	*dup;

// 	ft_dup = ft_strdup(str);
// 	dup = strdup(str);
// 	printf("ft: %s\n", ft_dup);
// 	printf("  : %s\n", dup);
// 	free(ft_dup);
// 	free(dup);
// 	return (0);
// }
