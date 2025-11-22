/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:12:01 by nkojima           #+#    #+#             */
/*   Updated: 2025/05/30 20:43:36 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	init_lookup_table(int *lookup, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		lookup[i] = 0;
		i++;
	}
}

static void	build_char_set(int *lookup, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		lookup[(unsigned char)set[i]] = 1;
		i++;
	}
}

static size_t	find_start_index(char const *s1, int *lookup)
{
	size_t	start;

	start = 0;
	while (s1[start] && lookup[(unsigned char)s1[start]])
		start++;
	return (start);
}

static size_t	find_end_index(char const *s1, size_t start, int *lookup)
{
	size_t	end;

	end = ft_strlen(s1);
	while (end > start && lookup[(unsigned char)s1[end - 1]])
		end--;
	return (end);
}

/**
 * Allocates and returns a copy of `s1` with any leading or
 * trailing characters found in `set` removed.
 *
 * Params:
 * @s1: The string to be trimmed.
 * @set: The string containing the set of characters to be removed.
 *
 * Return
 * A newly allocated trimmed string, or NULL on allocation failure.
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	int		lookup[256];

	init_lookup_table(lookup, sizeof(lookup) / sizeof(lookup[0]));
	build_char_set(lookup, set);
	start = find_start_index(s1, lookup);
	end = find_end_index(s1, start, lookup);
	return (ft_substr(s1, start, end - start));
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*s1;
// 	char	*set;

// 	s1 = "112233ABC12345ABC332211";
// 	set = "1234";
// 	printf("%s\n", ft_strtrim(s1, set));
// 	return (0);
// }
