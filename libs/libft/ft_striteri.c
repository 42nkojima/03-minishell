/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:14:50 by nkojima           #+#    #+#             */
/*   Updated: 2025/05/30 19:11:15 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Applies function `f` to each character of string `s`
 * `ft_striteri` receives the character's index and address
 * allowing it to modify the character if needed.
 *
 * Params:
 * @s: The string to iterate over
 * @f: The function to apply to each character
 */
void	ft_striteri(char *str, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		f(i, &str[i]);
		i++;
	}
}
// #include <stdio.h>

// static void	modify_case(unsigned int i, char *c)
// {
// 	if (i % 2 == 0 && *c >= 'a' && *c <= 'z')
// 		*c = *c - 32;
// 	else if (i % 2 == 1 && *c >= 'A' && *c <= 'Z')
// 		*c = *c + 32;
// }

// int	main(void)
// {
// 	char	str1[] = "Hello World";
// 	char	str2[] = "";

// 	printf("Original string 1: %s\n", str1);
// 	ft_striteri(str1, modify_case);
// 	printf("Modified string 1: %s\n", str1);
// 	printf("\nOriginal string 3: %s\n", str2);
// 	ft_striteri(str2, modify_case);
// 	printf("Modified string 3: %s\n", str2);
// 	return (0);
// }
