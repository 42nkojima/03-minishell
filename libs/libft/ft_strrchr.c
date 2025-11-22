/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 23:33:59 by nkojima           #+#    #+#             */
/*   Updated: 2025/05/30 20:09:11 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Returns a pointer to the last occurrence of the character c in the string s.
 *
 * Params:
 * @s: The string to search.
 * @c: The character to find.
 *
 * Return:
 * A pointer to the first occurrence of the character `c` in the string `s`,
 * or NULL if the character is not found.
 */
char	*ft_strrchr(const char *str, int c)
{
	size_t		len;
	char		cc;
	const char	*ptr;

	len = ft_strlen(str);
	cc = (char)c;
	ptr = str + len;
	while (1)
	{
		if (*ptr == cc)
			return ((char *)ptr);
		if (ptr == str)
			break ;
		ptr--;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	str[42] = "Hello, world!";

// 	printf("ft: %s\n", ft_strrchr(str, '!'));
// 	printf("  : %s\n", strrchr(str, '!'));
// 	printf("ft: %s\n", ft_strrchr(str, '\0'));
// 	printf("  : %s\n", strrchr(str, '\0'));
// 	return (0);
// }
