/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 11:21:28 by tshimizu          #+#    #+#             */
/*   Updated: 2026/02/20 16:04:19 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "constants.h"
#include <unistd.h>

void	free_redirects(t_redirect *redir)
{
	t_redirect	*next;

	while (redir)
	{
		next = redir->next;
		if (redir->heredoc_fd != HEREDOC_FD_UNSET)
			close(redir->heredoc_fd);
		free(redir->file);
		free(redir);
		redir = next;
	}
}

static void	free_cmd_data(t_cmd_data *cmd)
{
	if (!cmd)
		return ;
	free_string_array(cmd->argv);
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
