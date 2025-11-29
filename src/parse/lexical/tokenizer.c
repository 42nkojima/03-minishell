/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 15:51:04 by tshimizu          #+#    #+#             */
/*   Updated: 2025/11/29 16:39:48 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**tokenizer(char *input)
{
	if (!input)
		return (NULL);
	return (ft_split(input, ' '));
}

// Todo:milestone4で削除
// void print_tokens(char **tokens)
// {
//     int i = 0;

//     while (tokens && tokens[i])
//     {
//         printf("tokens[%d] = \"%s\"\n", i, tokens[i]);
//         i++;
//     }
// }
