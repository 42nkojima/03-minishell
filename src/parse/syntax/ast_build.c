/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 23:20:54 by tshimizu          #+#    #+#             */
/*   Updated: 2026/01/11 23:20:56 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*new_ast_node(t_node_type type)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	node->data.cmd = NULL;
	return (node);
}

t_ast_node	*new_pipe_node(t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*node;

	node = new_ast_node(NODE_PIPE);
	if (!node)
		return (NULL);
	node->left = left;
	node->right = right;
	return (node);
}

t_ast_node	*parse_pipeline(t_token *t, int l, int r)
{
	int	i;

	i = r;
	while (i >= l)
	{
		if (t[i].type == PIPE)
			return (new_pipe_node(parse_pipeline(t, l, i - 1), parse_pipeline(t,
						i + 1, r)));
		i--;
	}
	return (parse_cmd(t, l, r));
}

t_ast_node	*list_to_ast(t_token_list *token_list)
{
	return (parse_pipeline(token_list->tokens, 0, token_list->count - 1));
}
