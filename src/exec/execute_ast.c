/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 22:42:34 by nkojima           #+#    #+#             */
/*   Updated: 2026/01/25 23:14:41 by nkojima          ###   ########.fr       */
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

static int	execute_pipe_node(t_ast_node *node)
{
	int		fd[2];
	pid_t	left;
	pid_t	right;
	int		status_left;
	int		status_right;

	if (pipe(fd) == -1)
		return (1);
	left = fork();
	if (left == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		exit(execute_ast(node->left));
	}
	right = fork();
	if (right == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		exit(execute_ast(node->right));
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(left, &status_left, 0);
	waitpid(right, &status_right, 0);
	if (WIFEXITED(status_right))
		return (WEXITSTATUS(status_right));
	return (1);
}

int	execute_ast(t_ast_node *node)
{
	if (!node)
		return (0);
	if (node->type == NODE_CMD)
		return (execute_cmd_node(node));
	if (node->type == NODE_PIPE)
		return (execute_pipe_node(node));
	return (1);
}
