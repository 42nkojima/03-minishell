/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:10:54 by nkojima           #+#    #+#             */
/*   Updated: 2025/05/30 20:13:16 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Excerpts a substring from the string `s`.
 *
 * Params:
 * @s: The source string.
 * @start: The starting index of the substring.
 * @len: The maximum length of the substring.
 *
 * Return:
 * A newly allocated substring, or NULL on failure.
 */
char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	str_len;
	size_t	substr_len;

	str_len = ft_strlen(str);
	if ((size_t)start >= str_len)
		return (ft_calloc(1, 1));
	substr_len = str_len - (size_t)start;
	if (substr_len > len)
		substr_len = len;
	substr = malloc(sizeof(*substr) * (substr_len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < substr_len && str[start + i])
	{
		substr[i] = str[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*result;

// 	// テストケース 1: 通常の部分文字列
// 	result = ft_substr("Hello, world!", 7, 5);
// 	printf("Test 1: %s\n", result); // 期待値: "world"
// 	free(result);
// 	// テストケース 2: start が文字列の長さを超える
// 	result = ft_substr("Hello, world!", 20, 5);
// 	printf("Test 2: %s\n", result); // 期待値: ""
// 	free(result);
// 	// テストケース 3: len が文字列の残りの長さを超える
// 	result = ft_substr("Hello, world!", 7, 50);
// 	printf("Test 3: %s\n", result); // 期待値: "world!"
// 	free(result);
// 	// テストケース 4: 空文字列から部分文字列を取得
// 	result = ft_substr("", 0, 5);
// 	printf("Test 4: %s\n", result); // 期待値: ""
// 	free(result);
// 	// テストケース 5: len が 0 の場合
// 	result = ft_substr("Hello, world!", 7, 0);
// 	printf("Test 5: %s\n", result); // 期待値: ""
// 	free(result);
// 	// テストケース 6: NULL ポインタを渡す
// 	result = ft_substr(NULL, 0, 5);
// 	printf("Test 6: %s\n", result); // 期待値: 未定義動作（Cの設計思想に基づく）
// 	free(result);
// 	return (0);
// }
