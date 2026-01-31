/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 22:42:34 by nkojima           #+#    #+#             */
/*   Updated: 2026/01/25 23:35:12 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"

extern char		**environ;

static int	pipe_fork_fail(int fd[2], pid_t left)
{
	close(fd[0]);
	close(fd[1]);
	if (left > 0)
		waitpid(left, NULL, 0);
	return (EXIT_FAILURE);
}

static pid_t	fork_pipe_child(t_ast_node *node, int fd[2], int is_left)
{
	pid_t	pid;

	pid = fork();
	if (pid != SYSCALL_SUCCESS)
		return (pid);
	if (is_left)
		dup2(fd[1], STDOUT_FILENO);
	else
		dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	exit(execute_ast(node));
}

static int	execute_cmd_node(t_ast_node *node)
{
	t_command	cmd;

	if (!node->data.cmd->argv[0])
		return (EXIT_SUCCESS);
	cmd.argv = node->data.cmd->argv;
	cmd.envp = environ;
	return (execute_command(&cmd));
}

static int	execute_pipe_node(t_ast_node *node)
{
	int		fd[2];
	pid_t	left;
	pid_t	right;
	int		status_right;

	if (pipe(fd) == SYSCALL_ERROR)
		return (EXIT_FAILURE);
	left = fork_pipe_child(node->left, fd, 1);
	if (left == SYSCALL_ERROR)
		return (pipe_fork_fail(fd, -1));
	right = fork_pipe_child(node->right, fd, 0);
	if (right == SYSCALL_ERROR)
		return (pipe_fork_fail(fd, left));
	close(fd[0]);
	close(fd[1]);
	waitpid(left, NULL, 0);
	waitpid(right, &status_right, 0);
	if (WIFEXITED(status_right))
		return (WEXITSTATUS(status_right));
	return (EXIT_FAILURE);
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
