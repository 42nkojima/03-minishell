/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 02:45:17 by nkojima           #+#    #+#             */
/*   Updated: 2025/05/30 21:00:58 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Searches for the substring `find` in the string `str`.
 *
 * Params:
 * @str: The string to search in.
 * @find: The substring to search for.
 * @len: The maximum number of characters to search.
 *
 * Return:
 * - A pointer to the first occurrence of `find` in `str`.
 * - `NULL` if `find` is not found within the first `len` characters.
 */
char	*ft_strnstr(const char *str, const char *find, size_t len)
{
	size_t	find_len;

	find_len = ft_strlen(find);
	if (!find_len)
		return ((char *)str);
	while (*str && len >= find_len)
	{
		if (!ft_strncmp(str, find, find_len))
			return ((char *)str);
		str++;
		len--;
	}
	return (NULL);
}

// #include <bsd/string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	str[42] = "42Tokyo";
// 	char	find[42] = "";
// 	size_t	len;

// 	len = 42;
// 	printf("  : %p\n", strnstr(str, NULL, 0));
// 	printf("ft: %p\n", ft_strnstr(str, NULL, 0));
// 	return (0);
// }
