/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 11:14:22 by tshimizu          #+#    #+#             */
/*   Updated: 2025/12/21 18:14:39 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*new_pipe_node(t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = NODE_PIPE;
	node->left = left;
	node->right = right;
	return (node);
}

t_ast_node	*new_cmd_node(t_cmd_data *cmd)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = NODE_CMD;
	node->data.cmd = cmd;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_cmd_data *build_cmd_data(t_token *t, int l, int r)
{
	t_cmd_data	*cmd;

	cmd = malloc(sizeof(t_cmd_data));
	cmd->argv = extract_argv(t, l, r);
	cmd->redirects = extract_redirects(t, l, r);
	return (cmd);
}


t_ast_node *parse_cmd(t_token *t, int l, int r)
{
	t_ast_node	*node;
	t_cmd_data	*cmd;

	cmd = build_cmd_data(t, l, r);
	if (!cmd)
		return (NULL);
	node = new_ast_node(NODE_CMD);
	node->data.cmd = cmd;
	return (node);
}


t_ast_node *parse_pipeline(t_token *t, int l, int r)
{
	int	i;

	i = r;
	while (i >= l)
	{
		if (t[i].type == PIPE)
			return (new_pipe_node(
				parse_pipeline(t, l, i - 1),
				parse_pipeline(t, i + 1, r)));
		i--;
	}
	return (parse_cmd(t, l, r));
}

t_ast_node *list_to_ast(t_token_list *token_list)
{
	return (parse_pipeline(token_list->tokens,0,token_list->count - 1));
}
