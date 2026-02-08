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

static bool	has_expandable_mark(char *s, size_t i, char quote)
{
	return (quote == '"' && s[i] == '$' && (ft_isalpha(s[i + 1])
			|| s[i + 1] == '_' || s[i + 1] == '?'));
}

static size_t	find_quote_end(char *s, size_t i, char quote, bool *has_env)
{
	while (s[i] && s[i] != quote)
	{
		if (has_expandable_mark(s, i, quote))
			*has_env = true;
		i++;
	}
	return (i);
}

size_t	handle_quoted_word(t_token_list *list, char *s, size_t i,
		bool glued_left)
{
	char	quote;
	size_t	start;
	char	*word;
	bool	has_env;

	quote = s[i];
	i++;
	start = i;
	has_env = false;
	i = find_quote_end(s, i, quote, &has_env);
	if (!s[i])
	{
		list->error = ERR_UNCLOSED_QUOTE;
		return (i);
	}
	word = ft_substr(s, start, i - start);
	add_token(list, (t_token_init){.type = WORD, .value = word,
		.has_env = has_env, .single_quoted = quote == '\'',
		.quoted = true,
		.glued_left = glued_left});
	return (i + 1);
}
