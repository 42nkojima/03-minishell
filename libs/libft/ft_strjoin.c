/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:11:34 by nkojima           #+#    #+#             */
/*   Updated: 2025/05/30 19:13:22 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Concatenates two strings into a newly allocated string.
 *
 * Params:
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return:
 * A newly allocated string containing `s1` followed by `s2`,
	or NULL on failure.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	total_len;
	char	*joined;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	total_len = len1 + len2;
	joined = malloc(sizeof(*joined) * (total_len + 1));
	if (!joined)
		return (NULL);
	ft_memcpy(joined, s1, len1);
	ft_memcpy(joined + len1, s2, len2);
	joined[total_len] = '\0';
	return (joined);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*result;

// 	// テストケース 1: 通常の文字列結合
// 	result = ft_strjoin("Hello, ", "world!");
// 	printf("Test 1: %s\n", result); // 期待値: "Hello, world!"
// 	free(result);
// 	// テストケース 2: 空文字列と結合
// 	result = ft_strjoin("", "world!");
// 	printf("Test 2: %s\n", result); // 期待値: "world!"
// 	free(result);
// 	result = ft_strjoin("Hello, ", "");
// 	printf("Test 3: %s\n", result); // 期待値: "Hello, "
// 	free(result);
// 	// テストケース 4: 両方が空文字列
// 	result = ft_strjoin("", "");
// 	printf("Test 4: %s\n", result); // 期待値: ""
// 	free(result);
// 	// テストケース 5: NULL ポインタを渡す
// 	result = ft_strjoin(NULL, "world!");
// 	printf("Test 5: %s\n", result); // 期待値: 未定義動作（Cの設計思想に基づく）
// 	free(result);
// 	result = ft_strjoin("Hello, ", NULL);
// 	printf("Test 6: %s\n", result); // 期待値: 未定義動作（Cの設計思想に基づく）
// 	free(result);
// 	return (0);
// }
