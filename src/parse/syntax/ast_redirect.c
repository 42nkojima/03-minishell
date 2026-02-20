/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 23:20:08 by tshimizu          #+#    #+#             */
/*   Updated: 2026/02/01 16:08:35 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "constants.h"

static t_redirect	*new_redirect(t_redir_type type, char *value)
{
	t_redirect	*redir;

	redir = malloc(sizeof(t_redirect));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(value);
	redir->heredoc_fd = HEREDOC_FD_UNSET;
	redir->next = NULL;
	return (redir);
}

static t_redirect	*parse_one_redirect(t_token *t, int *i, int r)
{
	t_redirect	*new;

	if (*i + 1 > r || t[*i + 1].type != WORD)
		return (NULL);
	new = new_redirect(token_to_redir(t[*i].type), t[*i + 1].value);
	*i += 2;
	return (new);
}

static void	append_redirect(t_redirect **head, t_redirect **cur,
		t_redirect *new)
{
	if (!*head)
		*head = new;
	else
		(*cur)->next = new;
	*cur = new;
}

t_redirect	*extract_redirects(t_token *t, int l, int r)
{
	t_redirect	*head;
	t_redirect	*cur;
	t_redirect	*new;

	head = NULL;
	cur = NULL;
	while (l <= r)
	{
		if (is_redirection(t[l].type))
		{
			new = parse_one_redirect(t, &l, r);
			if (!new)
				return (free_redirects(head), NULL);
			append_redirect(&head, &cur, new);
		}
		else
			l++;
	}
	return (head);
}
