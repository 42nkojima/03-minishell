/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 11:49:28 by tshimizu          #+#    #+#             */
/*   Updated: 2025/12/21 14:19:51 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	scan_word(t_token_list *list, char *s, size_t i, bool joins_prev)
{
	size_t	start;
	bool	has_env;
	char	*word;

	start = i;
	has_env = false;
	while (s[i] && !ft_isspace(s[i]) && !is_operator(s[i]) && !is_quote(s[i]))
	{
		if (s[i] == '$' && (ft_isalpha(s[i + 1])
				|| s[i + 1] == '_' || s[i + 1] == '?'))
			has_env = true;
		i++;
	}
	word = ft_substr(s, start, i - start);
	token_list_push(list, (t_token_init){.type = WORD, .value = word,
		.has_env = has_env, .single_quoted = false, .is_quoted = false,
		.joins_prev = joins_prev});
	return (i);
}
