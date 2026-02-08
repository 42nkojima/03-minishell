/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 11:48:55 by tshimizu          #+#    #+#             */
/*   Updated: 2025/12/21 14:15:43 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static size_t	push_operator_token(t_token_list *list, t_token_type type,
		char *symbol, size_t next_i)
{
	token_list_push(list, (t_token_init){
		.type = type,
		.value = ft_strdup(symbol),
		.has_env = false,
		.single_quoted = false,
		.is_quoted = false,
		.joins_prev = false,
	});
	return (next_i);
}

size_t	scan_operator(t_token_list *list, char *s, size_t i)
{
	if (s[i] == '|')
		return (push_operator_token(list, PIPE, "|", i + 1));
	if (s[i] == '<' && s[i + 1] && s[i + 1] == '<')
		return (push_operator_token(list, HEREDOC, "<<", i + 2));
	if (s[i] == '>' && s[i + 1] && s[i + 1] == '>')
		return (push_operator_token(list, REDIR_APPEND, ">>", i + 2));
	if (s[i] == '<')
		return (push_operator_token(list, REDIR_IN, "<", i + 1));
	if (s[i] == '>')
		return (push_operator_token(list, REDIR_OUT, ">", i + 1));
	return (i);
}
