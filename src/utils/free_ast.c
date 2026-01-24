/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 11:21:28 by tshimizu          #+#    #+#             */
/*   Updated: 2026/01/11 23:05:13 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_redirects(t_redirect *redir)
{
	t_redirect	*next;

	while (redir)
	{
		next = redir->next;
		free(redir->file);
		free(redir);
		redir = next;
	}
}

void	free_cmd_data(t_cmd_data *cmd)
{
	if (!cmd)
		return ;
	free_argv(cmd->argv);
	free_redirects(cmd->redirects);
	free(cmd);
}

void	free_ast(t_ast_node *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->type == NODE_CMD)
		free_cmd_data(node->data.cmd);
	free(node);
}
