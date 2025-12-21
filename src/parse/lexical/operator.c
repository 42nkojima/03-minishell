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

size_t	handle_operator(t_token_list *list, char *s, size_t i)
{
	if (s[i] == '|')
		return (add_token(list, (t_token_init){.type = PIPE,
				.value = ft_strdup("|"), .has_env = false,
				.single_quoted = false}), i + 1);
	if (s[i] == '<' && s[i + 1] && s[i + 1] == '<')
		return (add_token(list, (t_token_init){.type = HEREDOC,
				.value = ft_strdup("<<"), .has_env = false,
				.single_quoted = false}), i + 2);
	if (s[i] == '>' && s[i + 1] && s[i + 1] == '>')
		return (add_token(list, (t_token_init){.type = REDIR_APPEND,
				.value = ft_strdup(">>"), .has_env = false,
				.single_quoted = false}), i + 2);
	if (s[i] == '<')
		return (add_token(list, (t_token_init){.type = REDIR_IN,
				.value = ft_strdup("<"), .has_env = false,
				.single_quoted = false}), i + 1);
	if (s[i] == '>')
		return (add_token(list, (t_token_init){.type = REDIR_OUT,
				.value = ft_strdup(">"), .has_env = false,
				.single_quoted = false}), i + 1);
	return (i);
}
