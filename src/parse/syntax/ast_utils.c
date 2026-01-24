/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 23:19:34 by tshimizu          #+#    #+#             */
/*   Updated: 2026/01/11 23:19:39 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir_type	token_to_redir(t_token_type type)
{
	if (type == REDIR_IN)
		return (AST_REDIR_IN);
	if (type == REDIR_OUT)
		return (AST_REDIR_OUT);
	if (type == REDIR_APPEND)
		return (AST_REDIR_APPEND);
	if (type == HEREDOC)
		return (AST_HEREDOC);
	return (AST_REDIR_INVALID);
}

bool	is_redirection(t_token_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT || type == REDIR_APPEND
		|| type == HEREDOC);
}

bool	is_redir_target(t_token *t, int i)
{
	if (i == 0 || t[i].type != WORD)
		return (false);
	return (is_redirection(t[i - 1].type));
}

bool	has_redir_in_range(t_token *t, int l, int r)
{
	while (l < r)
	{
		if (is_redirection(t[l].type))
			return (true);
		l++;
	}
	return (false);
}
