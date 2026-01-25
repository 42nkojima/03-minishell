/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 22:42:34 by nkojima           #+#    #+#             */
/*   Updated: 2026/01/25 23:06:32 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"

extern char	**environ;

static int	execute_cmd_node(t_ast_node *node)
{
	t_command	cmd;

	cmd.argv = node->data.cmd->argv;
	cmd.envp = environ;
	return (execute_command(&cmd));
}

int	execute_ast(t_ast_node *node)
{
	if (!node)
		return (0);
	if (node->type == NODE_CMD)
		return (execute_cmd_node(node));
	return (1);
}
