/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 11:49:28 by tshimizu          #+#    #+#             */
/*   Updated: 2025/12/21 12:26:00 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	handle_word(t_token_list *list, char *s, size_t i)
{
	size_t	start;
	bool	has_env;
	char	*word;

	start = i;
	has_env = false;
	while (s[i] && !ft_isspace(s[i]) && !is_operator(s[i]) && !is_quote(s[i]))
	{
		if (s[i] == '$' && (ft_isalpha(s[i + 1]) || s[i + 1] == '?'))
			has_env = true;
		i++;
	}
	word = ft_substr(s, start, i - start);
	add_token(list, WORD, word, has_env, false);
	return (i);
}
