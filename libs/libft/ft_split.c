/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:12:40 by nkojima           #+#    #+#             */
/*   Updated: 2025/05/30 18:55:54 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Count number of words in string */
static size_t	word_count(char const *str, char delim)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != delim && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*str == delim)
			in_word = 0;
		str++;
	}
	return (count);
}

/* Free allocated memory on error */
static void	free_split(char **array, size_t filled)
{
	size_t	i;

	i = 0;
	while (i < filled)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

/* Duplicate word with specific length */
static char	*word_dup(char const *start, size_t len)
{
	char	*word;

	word = malloc(len + 1);
	if (!word)
		return (NULL);
	ft_memcpy(word, start, len);
	word[len] = '\0';
	return (word);
}

/* Extract words and store them in array */
static int	populate_result(char **result, const char *str, char delim)
{
	size_t		i;
	const char	*start;

	i = 0;
	while (*str)
	{
		if (*str != delim)
		{
			start = str;
			while (*str && *str != delim)
				str++;
			result[i] = word_dup(start, str - start);
			if (!result[i])
			{
				free_split(result, i);
				return (0);
			}
			i++;
			continue ;
		}
		str++;
	}
	result[i] = NULL;
	return (1);
}

/**
 * Allocates memory (using malloc(3)) and returns an
 * array of strings obtained by splitting 'str' using
 * the character 'delim' as a delimiter. The array ends
 * with a NULL pointer.
 *
 * Params:
 *  @str:   The input string to split.
 *  @delim: The delimiter character.
 *
 * Return:
 *  A NULL-terminated array of substrings, or NULL on
 *  allocation failure.
 */
char	**ft_split(char const *str, char delim)
{
	char	**result;
	size_t	words;

	words = word_count(str, delim);
	result = malloc(sizeof(*result) * (words + 1));
	if (!result)
		return (NULL);
	if (!populate_result(result, str, delim))
		return (NULL);
	return (result);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	**result;
// 	int		i;

// 	// Test 1: Normal case with spaces
// 	printf("Test 1: \"hello world\" with space delimiter\n");
// 	result = ft_split("hello world", ' ');
// 	i = 0;
// 	while (result[i])
// 	{
// 		printf("  [%d]: \"%s\"\n", i, result[i]);
// 		i++;
// 	}
// 	printf("  Total words: %d\n\n", i);
// 	free_split(result, i);
// 	// Test 2: Multiple consecutive delimiters
// 	printf("Test 2: \"  multiple   spaces  \" with space delimiter\n");
// 	result = ft_split("  multiple   spaces  ", ' ');
// 	i = 0;
// 	while (result[i])
// 	{
// 		printf("  [%d]: \"%s\"\n", i, result[i]);
// 		i++;
// 	}
// 	printf("  Total words: %d\n\n", i);
// 	free_split(result, i);
// 	// Test 3: Empty string
// 	printf("Test 3: \"\" (empty string)\n");
// 	result = ft_split("", ',');
// 	i = 0;
// 	while (result[i])
// 	{
// 		printf("  [%d]: \"%s\"\n", i, result[i]);
// 		i++;
// 	}
// 	printf("  Total words: %d\n\n", i);
// 	free_split(result, i);
// 	// Test 4: String with only delimiters
// 	printf("Test 4: \",,,,\" (only delimiters)\n");
// 	result = ft_split(",,,,", ',');
// 	i = 0;
// 	while (result[i])
// 	{
// 		printf("  [%d]: \"%s\"\n", i, result[i]);
// 		i++;
// 	}
// 	printf("  Total words: %d\n\n", i);
// 	free_split(result, i);
// 	// Test 5: Different delimiter
// 	printf("Test 5: \"one,two,three\" with ',' delimiter\n");
// 	result = ft_split("one,two,three", ',');
// 	i = 0;
// 	while (result[i])
// 	{
// 		printf("  [%d]: \"%s\"\n", i, result[i]);
// 		i++;
// 	}
// 	printf("  Total words: %d\n\n", i);
// 	free_split(result, i);
// 	// Test 6: No delimiter in string
// 	printf("Test 6: \"hello\" with space delimiter\n");
// 	result = ft_split("hello", ' ');
// 	i = 0;
// 	while (result[i])
// 	{
// 		printf("  [%d]: \"%s\"\n", i, result[i]);
// 		i++;
// 	}
// 	printf("  Total words: %d\n\n", i);
// 	free_split(result, i);
// 	return (0);
// }
