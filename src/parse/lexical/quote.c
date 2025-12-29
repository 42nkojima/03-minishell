/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 11:48:07 by tshimizu          #+#    #+#             */
/*   Updated: 2025/12/21 14:24:50 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

size_t	handle_quoted_word(t_token_list *list, char *s, size_t i)
{
	char	quote;
	size_t	start;
	char	*word;
	bool	has_env;

	quote = s[i];
	i++;
	start = i;
	has_env = false;
	while (s[i] && s[i] != quote)
	{
		if (quote == '"'
			&& s[i] == '$' && (ft_isalpha(s[i + 1]) || s[i + 1] == '?'))
			has_env = true;
		i++;
	}
	if (!s[i])
	{
		list->error = ERR_UNCLOSED_QUOTE;
		return (i);
	}
	word = ft_substr(s, start, i - start);
	add_token(list, (t_token_init){.type = WORD, .value = word,
		.has_env = has_env, .single_quoted = quote == '\''});
	return (i + 1);
}
